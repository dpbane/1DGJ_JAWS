#pragma once

#include "enemy_base.h"


namespace game {

class DummyEnemy : public EnemyBase {
public:
  DummyEnemy(Terrain* terrain, const Vec2& position);
  ~DummyEnemy() override = default;

  void Setup() override;
  void Render(const Camera2D& camera) const override;
  void Release() override;
  Optional<int> UpdateOrder() const override { return 0; }
  Optional<int> RenderOrder() const override { return 0; }

  bool MainUpdate() override;
  bool OnHpZero() override;

};


}
