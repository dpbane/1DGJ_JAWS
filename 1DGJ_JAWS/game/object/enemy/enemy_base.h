#pragma once

#include "base_system/game_object/game_object.h"
#include "game/object/terrain/terrain.h"
#include "game/object/object_tag.h"

namespace game {

class EnemyBase abstract : public base::GameObject {
public:
  EnemyBase(Terrain* terrain) : terrain_(terrain) {}
  virtual ~EnemyBase() = default;

  virtual void Setup() = 0;
  virtual void Render(const Camera2D& camera) const = 0;
  virtual void Release() = 0;
  virtual Optional<int> UpdateOrder() const = 0;
  virtual Optional<int> RenderOrder() const = 0;

  bool Update() override;


  Optional<int> Tag() const override { return (int)ObjectTag::Enemy; }

  bool EnemyPreUpdate();
  bool EnemyPostUpdate();
  virtual bool MainUpdate() = 0;
  virtual bool OnHpZero() = 0;

  void TakeDamage(int damage) {
    hp_ = std::max(hp_ - damage, 0);
  }

  void RenderHitbox(const Camera2D& camera) const;

  Array<Rect> GetHitbox() const;
  Array<Rect> GetAttackbox() const;
  Optional<Rect> GetTerrainbox() const;
  int GetAtkPower() const { return atk_power_; }
  Vec2 GetPosition() const { return position_; }
  int GetHp() const { return hp_; }

protected:
  Vec2 position_ {};
  Vec2 velocity_ { 0, 0 };
  int previous_hp_ = 0, hp_ = 0;
  int atk_power_ = 0;
  Array<Rect> hitbox_ {};  // オブジェクトのくらい判定
  Array<Rect> attackbox_ {};  // オブジェクトの攻撃判定
  Optional<Rect> terrainbox_;  // 地形判定用
  bool on_ground_ { true };  // 着地していたらtrue
  bool is_flipped_ { false };  // 左右反転しているか
  float hitstop_ { 0.0f };  // ヒットストップ。単位は秒、0より大きいと有効。実装は継承先に任せる

  Terrain* terrain_ { nullptr };
};



}
