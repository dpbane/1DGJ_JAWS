#include "stdafx.h"
#include "game/object/player/player.h"

#include "game/reference.h"
#include "punch_param.h"

namespace game {

constexpr Player::StateEnum S = Player::StateEnum::PunchGround;

template<>
Optional<Player::StateEnum> Player::StateImpl<S>::Transition(Player& player) {
  if (player.motion_time_ >= kPunchRecovery) return StateEnum::Stand;
  return none;
}

template<>
void Player::StateImpl<S>::Update(Player& player) {
  player.motion_time_ += Scene::DeltaTime();
  player.velocity_.x = 0;
  player.attackbox_.clear();
  if (player.motion_time_ < kPunchStartup) {
    // 発生前
    player.frame_index_ = 1;

  }
  else if (player.motion_time_ < kPunchActive) {
    // 発生
    player.frame_index_ = 4;
    player.atk_power_ = kPunchDamage;
    player.attackbox_.push_back(kPunchBoxAct);
  }
  else {
    // 硬直
    player.frame_index_ = 4;
    player.atk_power_ = kPunchDamage;
    player.attackbox_.push_back(kPunchBoxRecv);
  }

}

}
