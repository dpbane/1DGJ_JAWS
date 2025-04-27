#include "stdafx.h"
#include "enemy_base.h"

namespace game {

bool EnemyBase::EnemyPreUpdate() {
  bool ret{ true };
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
  position_.x += velocity_.x * Scene::DeltaTime();
  double offset_x = 0;
  while (true) {
    const Point pos = Point((int)position_.x, (int)position_.y);
    const auto& box = terrainbox_.value().movedBy(pos);
    if (not terrain_->Conflict(box)) break;
    if (velocity_.x > 0) offset_x = -0.5;
    if (velocity_.x < 0) offset_x = 0.5;
    position_.x += offset_x;
    velocity_.x = 0;
  }

  // 次にY方向の位置更新
  position_.y += velocity_.y * Scene::DeltaTime();
  double offset_y = 0;
  while (true) {
    const Point pos = Point((int)position_.x, (int)position_.y);
    const auto& box = terrainbox_.value().movedBy(pos);
    if (not terrain_->Conflict(box)) break;
    if (velocity_.y > 0) offset_y = -0.5;
    if (velocity_.y < 0) offset_y = 0.5;
    position_.y += offset_y;
    velocity_.y = 0;
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
