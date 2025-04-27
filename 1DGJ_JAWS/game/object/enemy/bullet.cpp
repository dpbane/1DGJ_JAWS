#include "stdafx.h"
#include "bullet.h"

namespace game {

Bullet::Bullet(Terrain* terrain, const Vec2& position, const Vec2& velocity) :
  EnemyBase(terrain) {
  position_ = position;
  velocity_ = velocity;
  // 1固定にしちゃってる
  atk_power_ = 1;
  hp_ = 1;
  previous_hp_ = 1;
  terrainbox_ = Rect(-5, -5, 10, 10);
}

void Bullet::Setup() {
}

void Bullet::Render(const Camera2D& camera) const {
  {
    const auto t = camera.createTransformer();
  }
  RenderHitbox(camera);
}

void Bullet::Release() {
}

bool Bullet::MainUpdate() {
  EnemyPreUpdate();
  // TODO:とりあえず640で
  if (position_.x < -640) {
    return false;
  }
  EnemyPostUpdate();
  if (on_ground_) {
    return false;
  }
  return true;
}


}
