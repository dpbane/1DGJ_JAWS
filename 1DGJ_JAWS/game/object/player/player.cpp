#include "stdafx.h"
#include "player.h"

#include "base_system/game_object/game_object_manager.h"
#include "game/object/effect/hit_effect.h"

namespace game {

constexpr double kGravity = 2200.0;
constexpr double kMaxVelcity = 800.0;
constexpr double kJumpVelocity = -900.0;

constexpr double kKnockbackVelocityX = 180.0;
constexpr double kKnockbackVelocityY = -300.0;

Player::Player(Terrain* terrain, const Vec2& position) :
  EnemyBase(terrain) {
  position_ = position;
  velocity_ = Vec2(0, 0);
  atk_power_ = 3;
  hp_ = max_hp_;
  previous_hp_ = max_hp_;

  hitbox_.emplace_back(-30, -62, 60, 124);

  // 仮置き
  //attackbox_.emplace_back(-64, -32, 32, 32);

  terrainbox_ = Rect(-32, -64, 64, 128);

  SetState(StateEnum::Stand);

#define REGISTER(S)  state_map_[S] = std::make_unique<StateImpl<S>>();
  REGISTER(StateEnum::Stand);
  REGISTER(StateEnum::Walk);
  REGISTER(StateEnum::Air);
  REGISTER(StateEnum::Step);
  REGISTER(StateEnum::PunchGround);
  REGISTER(StateEnum::PunchAir);
  REGISTER(StateEnum::KickGround);
  REGISTER(StateEnum::KickAir);
  REGISTER(StateEnum::Knockback);
  REGISTER(StateEnum::Death);
#undef REGISTER
}

void Player::Setup() {
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

bool Player::MainUpdate() {
  attackbox_.clear();

  while (const auto new_state = state_map_.at(state_)->Transition(*this)) {
    SetState(new_state.value());
  }
  state_map_.at(state_)->Update(*this);

  InvinsibleProcess();
  GravityProcess();
  EnemyInteractProcess();

  return true;
}

void Player::SetState(StateEnum s) {
  state_ = s;
}

void Player::GravityProcess() {
  velocity_.y += kGravity * Scene::DeltaTime();
  velocity_.y = std::min(velocity_.y, kMaxVelcity);
}

void Player::EnemyInteractProcess() {
  auto enemy_array = gom_->Find((int)ObjectTag::Enemy);
  for (auto* enemy_object : enemy_array) {
    EnemyBase* enemy = reinterpret_cast<EnemyBase*>(enemy_object);

    // こちらの攻撃判定
    const bool hit = HitAgainst(enemy);
    if (hit && not attack_enemy_set_.contains(enemy)) {
      attack_enemy_set_.insert(enemy);
      enemy->TakeDamage(atk_power_);
    }
    if (not hit && attack_enemy_set_.contains(enemy)) {
      attack_enemy_set_.erase(enemy);
    }

    // 向こうの攻撃判定
    if (invinsible_time_ == 0.0 && TakeAgainst(enemy)) {
      TakeDamage(enemy->GetAtkPower());
      DoKnockback(enemy);
    }

  }
}

void Player::InvinsibleProcess() {
  if (invinsible_time_ <= 0) return;
  invinsible_time_ -= Scene::DeltaTime();
  if (invinsible_time_ < 0) invinsible_time_ = 0;
}

bool Player::HitAgainst(EnemyBase* enemy) {
  for (const auto& b : GetAttackbox()) {
    for (const auto& e : enemy->GetHitbox()) {
      if (b.intersects(e)) return true;
    }
  }
  return false;
}

bool Player::TakeAgainst(EnemyBase* enemy) {
  for (const auto& b : GetHitbox()) {
    for (const auto& e : enemy->GetAttackbox()) {
      if (b.intersects(e)) return true;
    }
  }
  return false;
}

void Player::DoJump() {
  velocity_.y = kJumpVelocity;
  SetState(StateEnum::Air);


}

void Player::DoKnockback(EnemyBase* enemy) {
  if (position_.x > enemy->GetPosition().x) {
    velocity_.x = kKnockbackVelocityX;
  }
  else {
    velocity_.x = -kKnockbackVelocityX;
  }
  velocity_.y = kKnockbackVelocityY;
  knockback_land_time_ = -1.0;
  SetState(StateEnum::Knockback);
}

void Player::DoPunch() {
  motion_time_ = 0;
  SetState(on_ground_ ? StateEnum::PunchGround : StateEnum::PunchAir);
}

void Player::DoKick() {
  motion_time_ = 0;
  SetState(on_ground_ ? StateEnum::KickGround : StateEnum::KickAir);
}

void Player::DoStep() {
  motion_time_ = 0;
  SetState(StateEnum::Step);
}

}
