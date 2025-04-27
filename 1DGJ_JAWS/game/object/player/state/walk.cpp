#include "stdafx.h"
#include "game/object/player/player.h"

#include "game/reference.h"

namespace game {

constexpr Player::StateEnum S = Player::StateEnum::Walk;

template<>
Optional<Player::StateEnum> Player::StateImpl<S>::Transition(Player& player) {
  // Air
  if (not player.on_ground_) {
    player.velocity_ = { 0, 0 };
    return Player::StateEnum::Air;
  }



  // Walk
  if (ref::MInput.Pressed(input::Action::Left) == ref::MInput.Pressed(input::Action::Right)) {
    return Player::StateEnum::Stand;
  }

  return none;
}

template<>
void Player::StateImpl<S>::Update(Player& player) {
}

}
