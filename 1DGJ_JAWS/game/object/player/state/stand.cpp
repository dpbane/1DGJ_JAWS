#include "stdafx.h"
#include "game/object/player/player.h"

#include "game/reference.h"

namespace game {

constexpr Player::StateEnum S = Player::StateEnum::Stand;

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
  if ((ref::MInput.Pressed(input::Action::Left) && not ref::MInput.Pressed(input::Action::Right)) ||
    (ref::MInput.Pressed(input::Action::Right) && not ref::MInput.Pressed(input::Action::Left))) {
    return Player::StateEnum::Walk;
  }

  return none;
}

template<>
void Player::StateImpl<S>::Update(Player& player) {
  player.velocity_ = { 0, 0 };
  player.frame_index_ = 1;

  if (ref::MInput.Down(input::Action::Jump)) player.DoJump();
}

}
