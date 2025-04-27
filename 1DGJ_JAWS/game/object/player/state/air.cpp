#include "stdafx.h"
#include "game/object/player/player.h"

#include "game/reference.h"

namespace game {

constexpr Player::StateEnum S = Player::StateEnum::Air;

template<>
Optional<Player::StateEnum> Player::StateImpl<S>::Transition(Player& player) {
  // Stand
  if (player.on_ground_) {
    player.velocity_ = { 0, 0 };
    return Player::StateEnum::Stand;
  }

  // Punch
  if (ref::MInput.Down(input::Action::Punch)) {
    player.DoPunch();
    return Player::StateEnum::PunchAir;
  }

  // Kick
  if (ref::MInput.Down(input::Action::Kick)) {
    player.DoKick();
    return Player::StateEnum::KickAir;
  }

  return none;
}

template<>
void Player::StateImpl<S>::Update(Player& player) {
  player.frame_index_ = 5;

  if (ref::MInput.Pressed(input::Action::Left) && not ref::MInput.Pressed(input::Action::Right)) {
    player.is_flipped_ = false;
  }
  if (ref::MInput.Pressed(input::Action::Right) && not ref::MInput.Pressed(input::Action::Left)) {
    player.is_flipped_ = true;
  }


}

}
