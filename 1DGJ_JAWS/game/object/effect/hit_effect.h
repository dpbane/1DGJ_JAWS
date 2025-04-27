#pragma once

#include "base_system/game_object/game_object.h"

namespace game {

class HitEffect : public base::GameObject {
public:

  static constexpr Vec2 Gravity { 0, 0 };

  struct Star
  {
    Vec2 start;
    Vec2 velocity;
    ColorF color;
  };

  Array<Star> m_stars;
  HitEffect(const Vec2& pos, double baseHue)
  {
    for (int32 i = 0; i < 3; ++i)
    {
      const Vec2 velocity = RandomVec2(Circle { 60 });
      Star star {
        .start = (pos + velocity * 0.5),
        .velocity = velocity,
        .color = HSV{ baseHue + Random(-60.0, 20.0) },
      };
      m_stars << star;
    }

    effect_frame_ = 0;
  }

  ~HitEffect() override = default;

  bool Update() override
  {
    for (auto& star : m_stars)
    {
      const Vec2 pos = (star.start + star.velocity * effect_frame_ * 5);
      const double angle = (pos.x * 3_deg);

      // サイズはいい感じに調整する
      Shape2D::Star((32 * (1.0 - effect_frame_ * 5)), pos, angle).draw(star.color);
    }

    if (effect_frame_ > 0.2) {
      // 消滅
      return false;
    }
    else {
      effect_frame_ += Scene::DeltaTime();
      return true;
    }
  }

  void Setup() override {}
  void Render(const Camera2D& camera) const override {}
  void Release() override {}

  Optional<int> UpdateOrder() const override { return 0; }
  Optional<int> RenderOrder() const override { return 10; }
  Optional<int> Tag() const override { return 1; }

private:
  double effect_frame_;
};
} // namespace game
