#include "stdafx.h"
#include "enemy_same.h"

namespace game {

Same::Same(Terrain* terrain, const Vec2& position) : EnemyBase(terrain) {
  position_ = position;
  move_verocity_ = Vec2 { -Random(500.0, 1500.0), -Random(500, 1500) };
  velocity_ = Vec2 { -20, 0 };
  previous_hp_ = 1, hp_ = 1;
  atk_power_ = 2;
  hitbox_.emplace_back(Point(-24, -24), Size(48, 48)); // 同一判定
  attackbox_.emplace_back(Point(-24, -24), Size(48, 48)); // 同一判定
  //texture_ = ref::MGraphic.GetTexture(graphic::Handle::Same);
  texture_ = Texture { U"🦈"_emoji };
  on_ground_ = false;
  reached_ = false;
};

void Same::Setup() {

}

bool Same::MainUpdate() {

  if (position_.x < 300) {
    // なんか接近したら動き出したい
    velocity_ = move_verocity_;
    velocity_ = velocity_ + Gravity;
  }
  else {

  }

  if (position_.x < -500) {
    // 消滅
    return false;
  }

  return true;
}

void Same::Render(const Camera2D& camera) const {
  RenderHitbox(camera);
  // サメを描画
  const auto t = camera.createTransformer();
  const Point pos = Point((int)position_.x, (int)position_.y);
  texture_.scaled(0.5).drawAt(position_);
}

bool Same::OnHpZero() {
  // 消滅
  return false;
}

void Same::Release() {

}

}


