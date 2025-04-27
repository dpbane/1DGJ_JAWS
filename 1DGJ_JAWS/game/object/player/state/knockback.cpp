#include "stdafx.h"
#include "game/object/player/player.h"

#include "game/reference.h"

namespace game {

constexpr Player::StateEnum S = Player::StateEnum::Knockback;

template<>
Optional<Player::StateEnum> Player::StateImpl<S>::Transition(Player& player) {
  if (player.on_ground_) {
    if (player.hp_ == 0) return StateEnum::Death;
    if (player.knockback_land_time_ == 0.0) return StateEnum::Stand;
  }
  return none;
}

template<>
void Player::StateImpl<S>::Update(Player& player) {
  if (player.on_ground_) {
    player.velocity_.x = 0;
    if (player.knockback_land_time_ < 0.0) {
      player.knockback_land_time_ = 0.3;
    }
  }

  if (player.knockback_land_time_ > 0) {
    player.knockback_land_time_ -= Scene::DeltaTime();
    if (player.knockback_land_time_ <= 0.0) {
      player.knockback_land_time_ = 0.0;
    }
  }
  player.invinsible_time_ = 1.0;
}

}
