#pragma once

#include "base_system/game_object/game_object.h"
#include "game/object/enemy/enemy_base.h"

namespace game {

class Player : public base::GameObject, public EnemyBase {
public:
  Player(Terrain* terrain, const Vec2& position);
  ~Player() = default;

  void Setup() override;
  bool Update() override;
  void Render(const Camera2D& camera) const override;
  void Release() override;

  bool OnHpZero() override { return true; }

  Optional<int> UpdateOrder() const override { return 100; }
  Optional<int> RenderOrder() const override { return 100; }
  Optional<int> Tag() const override { return 100; }

  int GetHp() const { return hp_; }
  int GetMaxHp() const { return max_hp_; }

  Vec2 GetPosition() const { return position_; }

private:
  int max_hp_ { 8 };

};


}
