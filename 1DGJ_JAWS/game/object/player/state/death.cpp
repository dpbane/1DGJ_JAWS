#include "stdafx.h"
#include "game/object/player/player.h"

#include "game/reference.h"

namespace game {

constexpr Player::StateEnum S = Player::StateEnum::Death;

template<>
Optional<Player::StateEnum> Player::StateImpl<S>::Transition(Player& player) {
  return none;
}

template<>
void Player::StateImpl<S>::Update(Player& player) {
  if (player.on_ground_) {
    player.velocity_.x = 0;
  }
  player.invinsible_time_ = 1.0;
}

}
