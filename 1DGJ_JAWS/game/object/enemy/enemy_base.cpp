#include "stdafx.h"
#include "enemy_base.h"

namespace game {

bool EnemyBase::EnemyPreUpdate() {
  bool ret { true };
  if (hp_ <= 0 && previous_hp_ > 0) ret = OnHpZero();
  previous_hp_ = hp_;
  return ret;
}

bool EnemyBase::EnemyPostUpdate() {
  // 地形との当たり判定がない場合はシンプル
  if (not terrainbox_) {
    position_ += velocity_ * Scene::DeltaTime();
    return true;
  }

  // まずX方向の位置更新
  {
    position_.x += velocity_.x * Scene::DeltaTime();
    const Point pos = Point((int)position_.x, (int)position_.y);
    const auto& box_raw = terrainbox_.value();
    const auto& box = terrainbox_.value().movedBy(pos);
    if (terrain_->Conflict(box)) {
      if (velocity_.x > 0) {
        position_.x = terrain_->NearestX(box.rightX()) - box_raw.rightX();
      }
      if (velocity_.x < 0) {
        position_.x = terrain_->NearestX(box.leftX()) - box_raw.leftX();
      }
      velocity_.x = 0;
    }
  }

  // 次にY方向の位置更新
  {
    position_.y += velocity_.y * Scene::DeltaTime();
    on_ground_ = false;
    const Point pos = Point((int)position_.x, (int)position_.y);
    const auto& box_raw = terrainbox_.value();
    const auto& box = terrainbox_.value().movedBy(pos);
    if (terrain_->Conflict(box)) {
      if (velocity_.y > 0) {
        position_.y = terrain_->NearestY(box.bottomY()) - box_raw.bottomY() + 1;  // 1ドットだけ下げて着地判定を継続
        on_ground_ = true;
      }
      if (velocity_.y < 0) {
        position_.y = terrain_->NearestX(box.topY()) - box_raw.topY();
      }
      velocity_.y = 0;
    }
  }

  return true;
}

void EnemyBase::RenderHitbox(const Camera2D& camera) const {
  const auto t = camera.createTransformer();
  const Point pos = Point((int)position_.x, (int)position_.y);

  for (const auto& box : hitbox_) {
    box.movedBy(pos).draw(ColorF(0.2, 0.2, 0.9, 0.6))
      .drawFrame(1.0, ColorF(0.3, 0.3, 1.0));
  }

  for (const auto& box : attackbox_) {
    box.movedBy(pos).draw(ColorF(0.9, 0.2, 0.2, 0.6))
      .drawFrame(1.0, ColorF(1.0, 0.3, 0.3));
  }

  if (terrainbox_) {
    terrainbox_->movedBy(pos).draw(ColorF(0.2, 0.9, 0.2, 0.6))
      .drawFrame(1.0, ColorF(0.3, 1.0, 0.3));
  }
}

}
