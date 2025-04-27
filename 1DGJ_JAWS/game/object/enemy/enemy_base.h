#pragma once

#include "game/object/terrain/terrain.h"

namespace game {

class EnemyBase {
public:
  EnemyBase(Terrain* terrain) : terrain_(terrain) {}
  virtual ~EnemyBase() = default;

  bool EnemyPreUpdate();
  bool EnemyPostUpdate();

  virtual bool OnHpZero() = 0;

  void TakeDamage(int damage) {
    hp_ = std::max(hp_ - damage, 0);
  }

  void RenderHitbox(const Camera2D& camera) const;

protected:
  Vec2 position_ {};
  Vec2 velocity_ { 0, 0 };
  int previous_hp_ = 0, hp_ = 0;
  int atk_power_ = 0;
  Array<Rect> hitbox_ {};  // オブジェクトのくらい判定
  Array<Rect> attackbox_ {};  // オブジェクトの攻撃判定
  Optional<Rect> terrainbox_;  // 地形判定用
  bool on_ground_ { true };  // 着地していたらtrue

  Terrain* terrain_ { nullptr };
};



}
