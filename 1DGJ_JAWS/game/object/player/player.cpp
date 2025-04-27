#include "stdafx.h"
#include "player.h"


namespace game {

Player::Player(const Vec2& position) {
  position_ = position;
}

void Player::Setup() {
}

bool Player::Update() {

  Camera2D cam;
  cam.update();
  //cam.setTargetCenter(position_);

  position_ += velocity_ * Scene::DeltaTime();
  return true;
}

void Player::Render(const Camera2D& camera) const {

  const auto t = camera.createTransformer();

  Circle(position_, 10).draw(Palette::Red);


}

void Player::Release() {
}





}
