#include "stdafx.h"
#include "rat.h"

#include "base_system/game_object/game_object_manager.h"
#include "game/graphic/graphic_enum.h"
#include "game/reference.h"

namespace game {

constexpr double kGravity = 1200.0;
constexpr double kMaxVelcity = 800.0;
constexpr double kJumpVelocity = -500.0;

Rat::Rat(Terrain* terrain, const Vec2& position) :
  EnemyBase(terrain) {
  position_ = position;
  velocity_ = Vec2(0, -500);
  // 1固定にしちゃってる
  atk_power_ = 1;
  hp_ = 1;
  previous_hp_ = 1;
  //TODO:サイズ未設定
  terrainbox_ = Rect(-5, -5, 10, 10);
}

void Rat::Setup() {
}

bool compFirstJump = false;
bool Rat::MainUpdate() {
  GravityProcess();
  if (compFirstJump) {
    velocity_ = Vec2(-100, 0);
  }
  //TODO:640でいい？
  if (position_.x < -640) {
    return false;
  }
  if (on_ground_) {
    compFirstJump = true;
  }
  return true;
}

void Rat::Render(const Camera2D& camera) const {
  {
    const auto t = camera.createTransformer();
    //TODO:デカイけど仮で画像追加
    ref::MGraphic.GetTexture(graphic::Handle::Rat).draw(position_ - Vec2(256, 412));
  }
  RenderHitbox(camera);
}

void Rat::Release() {
}

void Rat::GravityProcess() {
  velocity_.y += kGravity * Scene::DeltaTime();
  velocity_.y = std::min(velocity_.y, kMaxVelcity);
}




}
