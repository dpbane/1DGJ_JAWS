#include "stdafx.h"
#include "window_manager.h"

namespace base {

void WindowManager::Setup(int width, int height, const String& title, TextureFilter filter) {
  Scene::SetBackground(ColorF { 0.0, 0.0, 0.0 });  // シーンの背景色を黒に設定
  Scene::SetLetterbox(ColorF { 0, 0, 0 });  // レターボックスの色を黒に設定

  Scene::SetResizeMode(ResizeMode::Keep);  // シーンサイズ固定
  Window::Resize(width, height);
  Scene::Resize(width, height);
  Scene::SetTextureFilter(filter);

  Window::SetTitle(title);  // ウィンドウのタイトルを設定

}

}
