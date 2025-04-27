#include "ui_button_start.h"

namespace game {

UiButtonStart::UiButtonStart(const Rect& rect) {
  text_ = U"いてこますならクリック";
  rect_ = rect;
}

void UiButtonStart::Setup() {
  // nothing
}

bool UiButtonStart::Update() {
  return true;
  // キーが押される
  //return rect_.leftClicked();
}

void UiButtonStart::Render(const Camera2D& camera) const {
  const auto t = camera.createTransformer();
  // 影と背景を描く
  rect_
    .drawShadow(Vec2 { 2, 2 }, 12, 0)
    .draw(ColorF { 0.9, 0.8, 0.6 });

  // 枠を描く
  rect_.stretched(-3).rounded(3)
    .drawFrame(2, ColorF { 0.4, 0.3, 0.2 });

  // テキストを描く
  font(text_).drawAt(40, rect_.center(), ColorF { 0.4, 0.3, 0.2 });
}

void UiButtonStart::Release() {

}

}
