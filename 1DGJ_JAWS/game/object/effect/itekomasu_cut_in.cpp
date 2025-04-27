#include "stdafx.h"
#include "itekomasu_cut_in.h"

#include "game/reference.h"

namespace game {

ItekomasuCutIn::ItekomasuCutIn(const Vec2& position) {
  base_position_ = position;
  effect_frame_ = 0;
  texture_ = ref::MGraphic.GetTexture(graphic::Handle::Itekoma);
}

void ItekomasuCutIn::Setup() {
  // 画像読み込みはほんとはここ？
}
bool ItekomasuCutIn::Update() {
  // positionをがたがた揺らす
  // 揺れ幅は要調整
  position_ = Vec2 { (base_position_.x+ Random(1,5)), (base_position_.y + Random(1,5)) };

  if (effect_frame_ > 0.2) {
    // 消滅
    effect_frame_ = 0;
    return true;
    //return false;
  }
  else {
    effect_frame_ += Scene::DeltaTime();
    return true;
  }
}
void ItekomasuCutIn::Render(const Camera2D& camera) const {
  const auto t = camera.createTransformer();

  texture_.scaled(0.8).drawAt(position_); // サイズ感は要調整
}
void ItekomasuCutIn::Release() {

}

}
