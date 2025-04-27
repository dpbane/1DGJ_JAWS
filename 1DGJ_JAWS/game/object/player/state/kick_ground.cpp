#include "stdafx.h"
#include "game/object/player/player.h"

#include "game/reference.h"

namespace game {

constexpr Player::StateEnum S = Player::StateEnum::KickGround;

template<>
Optional<Player::StateEnum> Player::StateImpl<S>::Transition(Player& player) {
  return none;
}

template<>
void Player::StateImpl<S>::Update(Player& player) {
}

}
