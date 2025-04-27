#include "stdafx.h"
#include "fade.h"

namespace game {

Fade::Fade(const Rect& rect) {
  rect_ = rect;
  alpha_ = 0.0;
}

bool Fade::Update() {
  // 透明度を変化させる
  alpha_ += Scene::DeltaTime();

  if (alpha_ < 1) {
    return true;
  }
  else {
    rect_.draw(ColorF { 0, 0, 0, 1 });
    return true;
  }
}

void Fade::Render(const Camera2D& camera) const {
  {
    //const auto t = camera.createTransformer();
    rect_.draw(ColorF { 0, 0, 0, alpha_ });
  }
}

}

