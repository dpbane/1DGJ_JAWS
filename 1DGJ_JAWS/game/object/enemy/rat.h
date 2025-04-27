#pragma once

#include "base_system/game_object/game_object.h"
#include "game/object/enemy/enemy_base.h"
#include "game/object/object_tag.h"

namespace game {

class Rat : public EnemyBase {
public:
  Rat(Terrain* terrain, const Vec2& position);
  ~Rat() = default;

  void Setup() override;
  void Render(const Camera2D& camera) const override;
  void Release() override;

  bool MainUpdate() override;
  bool OnHpZero() override { return true; }

  Optional<int> UpdateOrder() const override { return 100; }
  Optional<int> RenderOrder() const override { return 100; }
  Optional<int> Tag() const override { return (int)(ObjectTag::Enemy); }

  Vec2 GetPosition() const { return position_; }

private:
  void GravityProcess();
};


}
