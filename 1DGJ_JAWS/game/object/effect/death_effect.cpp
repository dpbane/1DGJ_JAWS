#include "stdafx.h"
#include "death_effect.h"

namespace game {

DeathEffect::DeathEffect(const Vec2& pos) {
  position_ = pos;
}

bool DeathEffect::Update() {
  position_ += Vec2(3, 0);
  if (effect_frame_ > 2.0) {
    // 消滅
    return false;
  } else {
    effect_frame_ += Scene::DeltaTime();
    visible = int(effect_frame_ * 10) % 2 == 0;
    return true;
  }
}

void DeathEffect::Render(const Camera2D& camera) const {
  const auto t = camera.createTransformer();
  if (visible) {
    Circle(position_, effect_frame_ * 20).draw(Palette::Aqua);
  }
  else {
    Circle(position_, effect_frame_ * 20).draw(Palette::White);
  }

}

}

