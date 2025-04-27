#include "stdafx.h"
#include "player.h"

#include "base_system/game_object/game_object_manager.h"
#include "game/object/effect/hit_effect.h"

namespace game {

constexpr double kGravity = 300.0;
constexpr double kMaxVelcity = 500.0;

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
  velocity_.y = std::min(velocity_.y, kMaxVelcity);



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
