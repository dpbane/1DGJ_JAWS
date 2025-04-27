#include "stdafx.h"
#include "game/object/player/player.h"

#include "game/reference.h"

namespace game {

constexpr Player::StateEnum S = Player::StateEnum::Walk;

constexpr double kWalkSpeed = 200.0;

template<>
Optional<Player::StateEnum> Player::StateImpl<S>::Transition(Player& player) {
  // Air
  if (not player.on_ground_) {
    player.velocity_ = { 0, 0 };
    return Player::StateEnum::Air;
  }

  // Punch
  if (ref::MInput.Down(input::Action::Punch)) {
    player.DoPunch();
    return Player::StateEnum::PunchGround;
  }

  // Kick
  if (ref::MInput.Down(input::Action::Kick)) {
    player.DoKick();
    return Player::StateEnum::KickGround;
  }

  // Step
  if (ref::MInput.Down(input::Action::Step)) {
    player.DoStep();
    return Player::StateEnum::Step;
  }

  // Walk
  if (ref::MInput.Pressed(input::Action::Left) == ref::MInput.Pressed(input::Action::Right)) {
    return Player::StateEnum::Stand;
  }

  return none;
}

template<>
void Player::StateImpl<S>::Update(Player& player) {
  player.motion_time_ += Scene::DeltaTime();

  player.frame_index_ = 2 + int(player.motion_time_ / 0.2) % 2;

  if (ref::MInput.Pressed(input::Action::Left)) {
    player.velocity_.x = -kWalkSpeed;
    player.is_flipped_ = false;
  }
  if (ref::MInput.Pressed(input::Action::Right)) {
    player.velocity_.x = kWalkSpeed;
    player.is_flipped_ = true;
  }

  if (ref::MInput.Down(input::Action::Jump)) player.DoJump();
}

}
