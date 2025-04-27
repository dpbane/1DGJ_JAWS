#include "stdafx.h"
#include "game/object/player/player.h"

#include "game/reference.h"

namespace game {

constexpr double kStepSpeed = 500.0;
constexpr double kStepDump = 0.9;
constexpr double kStepActive = 0.1;
constexpr double kStepTotal = 0.8;

constexpr Player::StateEnum S = Player::StateEnum::Step;

template<>
Optional<Player::StateEnum> Player::StateImpl<S>::Transition(Player& player) {
  if (player.motion_time_ > kStepTotal) return StateEnum::Stand;
  return none;
}

template<>
void Player::StateImpl<S>::Update(Player& player) {
  player.motion_time_ += Scene::DeltaTime();

  if (player.motion_time_ < kStepActive) {
    player.velocity_.x = player.is_flipped_ ? kStepSpeed : -kStepSpeed;
    player.invinsible_time_ = 0.1;
  }
  else {
    player.velocity_.x *= kStepDump;
    player.invinsible_time_ = 0;
  }
}

}
