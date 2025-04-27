#include "stdafx.h"
#include "dummy.h"

namespace game {

DummyEnemy::DummyEnemy(Terrain* terrain, const Vec2& position) : EnemyBase(terrain) {
  position_ = position;
  velocity_ = { 0, 0 };
  previous_hp_ = 10, hp_ = 10;
  atk_power_ = 1;
  hitbox_.emplace_back(Point(-32, -32), Size(64, 64));
  attackbox_.emplace_back(Point(-16, -64), Size(32, 32));
  terrainbox_;
}

void DummyEnemy::Setup() {
}

void DummyEnemy::Render(const Camera2D& camera) const {
  RenderHitbox(camera);

  Print << U"Dummy HP: {}\n"_fmt(hp_);
}

void DummyEnemy::Release() {
}

bool DummyEnemy::MainUpdate() {
  return true;
}

bool DummyEnemy::OnHpZero() {
  return false;
}


}
