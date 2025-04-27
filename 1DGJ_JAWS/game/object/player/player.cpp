#include "stdafx.h"
#include "player.h"


namespace game {

constexpr double kGravity = 200.0;

Player::Player(Terrain* terrain, const Vec2& position) :
  EnemyBase(terrain) {
  position_ = position;
  velocity_ = Vec2(0, 0);
  atk_power_ = 3;

  hp_ = max_hp_;
  previous_hp_ = max_hp_;

  terrainbox_ = Rect(-32, -64, 64, 128);

}

void Player::Setup() {
}

bool Player::Update() {
  EnemyPreUpdate();

  velocity_.y += kGravity * Scene::DeltaTime();

  EnemyPostUpdate();
  return true;
}

void Player::Render(const Camera2D& camera) const {
  {
    const auto t = camera.createTransformer();
    Circle(position_, 10).draw(Palette::Red);
  }
  RenderHitbox(camera);
}

void Player::Release() {
}





}
