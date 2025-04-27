#include "stdafx.h"
#include "ninja.h"

#include "game/reference.h"

namespace game {

Ninja::Ninja(Terrain* terrain, const Vec2& position) : EnemyBase(terrain) {
  position_ = position;
  velocity_ = { 0, 0 };
  previous_hp_ = 10, hp_ = 10;
  atk_power_ = 1;
  hitbox_.emplace_back(Point(-30, -30), Size(90, 90));
  attackbox_.emplace_back(Point(-30, -30), Size(90, 90));
  terrainbox_ = Rect { Point(-34, -34), Size(98, 98) };
}

void Ninja::Render(const Camera2D& camera) const {
  {
    const auto t = camera.createTransformer();

    auto tex = ref::MGraphic.GetTextureRegion(graphic::Handle::Ninja, 1);
    if (is_flipped_) tex = tex.mirrored();
    tex.drawAt(position_);

  }

  RenderHitbox(camera);
}

bool Ninja::MainUpdate() {
  return true;
}

bool Ninja::OnHpZero() {
  return true;
}


}
