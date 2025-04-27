#include "stdafx.h"
#include "fade.h"

namespace game {

Fade::Fade() {
}

bool Fade::Update() {
  // 透明度を変化させる
  alpha_ += Scene::DeltaTime();

  if (to_black_) {
    alpha_ += Scene::DeltaTime() * fade_time_inv_;
  }
  else {
    alpha_ -= Scene::DeltaTime() * fade_time_inv_;
  }
  alpha_ = std::clamp(alpha_, 0.0, 1.0);
  return true;
}

void Fade::Render(const Camera2D& camera) const {
  Rect(0, 0, Scene::Width(), Scene::Height()).draw(ColorF { 0, 0, 0, alpha_ });
}

void Fade::SetFadeBlack(double time) {
  to_black_ = true;
  fade_time_inv_ = 1.0 / time;
  alpha_ = 0;
}

void Fade::SetFadeWhite(double time) {
  to_black_ = false;
  fade_time_inv_ = 1.0 / time;
  alpha_ = 1;
}

void Fade::SetWhite() {
  to_black_ = false;
  alpha_ = 0;
}

}

