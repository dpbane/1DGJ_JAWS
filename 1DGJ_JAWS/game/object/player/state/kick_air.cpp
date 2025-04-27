#include "stdafx.h"
#include "game/object/player/player.h"

#include "game/reference.h"
#include "kick_param.h"

namespace game {

constexpr Player::StateEnum S = Player::StateEnum::KickAir;

Optional<Player::StateEnum> Player::StateImpl<S>::Transition(Player& player) {
  if (player.motion_time_ > kKickRecovery) return StateEnum::Air;
  if (player.on_ground_) return StateEnum::KickGround;
  return none;
}

template<>
void Player::StateImpl<S>::Update(Player& player) {
  player.motion_time_ += Scene::DeltaTime();
  if (player.motion_time_ < kKickStartup) {
    // 発生前

  }
  else if (player.motion_time_ < kKickActive) {
    // 発生
    player.atk_power_ = kKickDamage;
    player.attackbox_.push_back(kKickBoxAct);
  }
  else {
    // 硬直
    player.atk_power_ = kKickDamage;
    player.attackbox_.push_back(kKickBoxRecv);
  }
}

}
