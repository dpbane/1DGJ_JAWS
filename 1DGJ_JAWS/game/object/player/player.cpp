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

  SetState(StateEnum::Stand);

#define REGISTER(S)  state_map_[S] = std::make_unique<StateImpl<S>>();
  REGISTER(StateEnum::Stand);
  REGISTER(StateEnum::Walk);
  REGISTER(StateEnum::Air);
  REGISTER(StateEnum::Guard);
  REGISTER(StateEnum::StepFront);
  REGISTER(StateEnum::StepBack);
  REGISTER(StateEnum::PunchGround);
  REGISTER(StateEnum::PunchAir);
  REGISTER(StateEnum::KickGround);
  REGISTER(StateEnum::KickAir);
#undef REGISTER
}

void Player::Setup() {
}

bool Player::Update() {
  EnemyPreUpdate();

  while (const auto new_state = state_map_.at(state_)->Transition(*this)) {
    SetState(new_state.value());
  }
  state_map_.at(state_)->Update(*this);

  velocity_.y += kGravity * Scene::DeltaTime();
  velocity_.y = std::min(velocity_.y, kMaxVelcity);

  EnemyPostUpdate();
  return true;
}

void Player::Render(const Camera2D& camera) const {
  {
    const auto t = camera.createTransformer();
    Circle(position_, 10).draw(Palette::Red);

    Print << U"State: {}\n"_fmt(std::to_underlying<StateEnum>(state_));
    Print << U"Y: {}\n"_fmt(position_.y);

  }
  RenderHitbox(camera);
}

void Player::Release() {
}

void Player::SetState(StateEnum s) {
  state_ = s;
}





}
