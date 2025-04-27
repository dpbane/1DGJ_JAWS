#include "stdafx.h"
#include "enemy_base.h"

namespace game {

bool EnemyBase::Update() {
  if (not EnemyPreUpdate()) return false;
  if (not MainUpdate()) return false;
  if (not EnemyPostUpdate()) return false;
  return true;
}

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
    const auto& box = GetTerrainbox().value();
    if (terrain_->Conflict(box)) {
      if (velocity_.x > 0) {
        position_.x = terrain_->NearestX(box.rightX()) - box_raw.rightX();
      }
      if (velocity_.x < 0) {
        position_.x = terrain_->NearestX(box.leftX()) - box_raw.leftX();
      }
      //velocity_.x = 0;
    }
  }

  // 次にY方向の位置更新
  {
    position_.y += velocity_.y * Scene::DeltaTime();
    const Point pos = Point((int)position_.x, (int)position_.y);
    const auto& box_raw = terrainbox_.value();
    const auto& box = GetTerrainbox().value();
    if (terrain_->Conflict(box)) {
      if (velocity_.y >= 0) {
        position_.y = terrain_->NearestY(box.bottomY()) - box_raw.bottomY();
      }
      if (velocity_.y < 0) {
        position_.y = terrain_->NearestX(box.topY()) - box_raw.topY();
      }
      velocity_.y = 0;
    }

    on_ground_ = false;
    const auto& box_ground = box.movedBy(Point(0, 1));
    if (terrain_->Conflict(box_ground)) {
      position_.y = terrain_->NearestY(box.bottomY()) - box_raw.bottomY();
      on_ground_ = true;
    }
  }

  return true;
}

void EnemyBase::RenderHitbox(const Camera2D& camera) const {
  const auto t = camera.createTransformer();
  const Point pos = Point((int)position_.x, (int)position_.y);

  for (const auto& box : GetHitbox()) {
    box.draw(ColorF(0.2, 0.2, 0.9, 0.3))
      .drawFrame(1.0, ColorF(0.3, 0.3, 1.0));
  }

  for (const auto& box : GetAttackbox()) {
    box.draw(ColorF(0.9, 0.2, 0.2, 0.3))
      .drawFrame(1.0, ColorF(1.0, 0.3, 0.3));
  }

  if (const auto box = GetTerrainbox()) {
    box->draw(ColorF(0.2, 0.9, 0.2, 0.3))
      .drawFrame(1.0, ColorF(0.3, 1.0, 0.3));
  }
}

Array<Rect> EnemyBase::GetHitbox() const {
  const Point pos = Point((int)position_.x, (int)position_.y);
  Array<Rect> ret;
  for (const auto& box : hitbox_) {
    if (is_flipped_) {
      ret.push_back(Rect(Point { -box.rightX(), box.y }, box.size).movedBy(pos));
    }
    else {
      ret.push_back(box.movedBy(pos));
    }
  }
  return ret;
}

Array<Rect> EnemyBase::GetAttackbox() const {
  const Point pos = Point((int)position_.x, (int)position_.y);
  Array<Rect> ret;
  for (const auto& box : attackbox_) {
    if (is_flipped_) {
      ret.push_back(Rect(Point { -box.rightX(), box.y }, box.size).movedBy(pos));
    }
    else {
      ret.push_back(box.movedBy(pos));
    }
  }
  return ret;
}

Optional<Rect> EnemyBase::GetTerrainbox() const {
  if (not terrainbox_.has_value()) return none;
  const Point pos = Point((int)position_.x, (int)position_.y);
  if (is_flipped_) {
    return Rect { Point{ -terrainbox_->rightX(), terrainbox_->y }, terrainbox_->size }.movedBy(pos);
  }
  return terrainbox_->movedBy(pos);
}

}
