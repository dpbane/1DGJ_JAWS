#include "stdafx.h"
#include "title_image.h"

#include "game/reference.h"

namespace game {

TitleImage::TitleImage(const Vec2& position) {
  base_position_ = position;
  texture_ = ref::MGraphic.GetTexture(graphic::Handle::Itekoma);
}

void TitleImage::Setup() {
}
bool TitleImage::Update() {
  // positionをがたがた揺らす
  // 揺れ幅は要調整
  position_ = Vec2 { (base_position_.x + Random(1,20)), (base_position_.y + Random(1,20)) };
  return true;
}
void TitleImage::Render(const Camera2D& camera) const {
  // const auto t = camera.createTransformer();
  //texture_.scaled(0.8).draw(); // サイズ感は要調整
  // なんかずれるのでcamera参照しないでもよいかも
  texture_.scaled(0.5).drawAt(position_); // サイズ感は要調整

  //texture_.drawAt(position_); // サイズ感は要調整

}
void TitleImage::Release() {

}

}
