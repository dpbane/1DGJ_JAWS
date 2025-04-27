#include "stdafx.h"
#include "hit_effect.h"

namespace game {

HitEffect::HitEffect(const Vec2& pos, double baseHue)
{
  for (int32 i = 0; i < 5; ++i)
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

bool HitEffect::Update()
{
  if (effect_frame_ > 0.2) {
    // 消滅
    return false;
  }
  else {
    effect_frame_ += Scene::DeltaTime();
    return true;
  }
}

void HitEffect::Render(const Camera2D& camera) const {
  for (auto& star : m_stars)
  {
    const Vec2 pos = (star.start + star.velocity * effect_frame_ * 5);
    const double angle = (pos.x * 3_deg);

    // サイズはいい感じに調整する
    // ほんとはRenderに分けたほうが良い?
    Shape2D::Star((16 * (1.0 - effect_frame_ * 5)), pos, angle).draw(star.color);
  }

}

}

