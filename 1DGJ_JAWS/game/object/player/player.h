#pragma once

#include "base_system/game_object/game_object.h"
#include "game/object/enemy/enemy_base.h"

namespace game {

class Player : public base::GameObject, public EnemyBase {
public:
  Player(const Vec2& position);
  ~Player() = default;

  void Setup() override;
  bool Update() override;
  void Render(const Camera2D& camera) const override;
  void Release() override;

  bool OnHpZero() override { return true; }

  Optional<int> UpdateOrder() const override { return 100; }
  Optional<int> RenderOrder() const override { return 100; }
  Optional<int> Tag() const override { return 100; }

private:


};


}
