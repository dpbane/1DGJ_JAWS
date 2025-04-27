#include "stdafx.h"
#include "title.h"

//#include "game/object/ui/ui_master.h"

namespace scene {

Title::Title(const InitData& init) : IScene { init } {
  // タイトルロゴ
  m_object_.Add(std::make_unique<game::TitleImage>(Vec2 { 640,200 })); // あとで画像差し替えしたい

  // button
  m_object_.Add(std::make_unique<game::UiButtonStart>(Rect(Arg::center(0, 100), 700, 80))); // Start
  //m_object_.Add(std::make_unique<game::UiButtonConfig>(Rect(Arg::center(0, 100), 300, 80))); // Config
  //m_object_.Add(std::make_unique<game::UiButtonEnd>(Rect(Arg::center(0, 200), 300, 80))); // End

  // タイトル曲
  //m_object_.Add(std::make_unique<audio>(Rect(Arg::center(0, 100), 300, 80))); // Start

}

void Title::update() {

  m_object_.Update();
  if (KeySpace.pressed()) {
    // Stage1 開始
    // とりまSpace
    changeScene(scene::SceneEnum::Level1, 0s);
  }
}

void Title::draw() const {
  ClearPrint();
  Print << Profiler::FPS() << U" FPS\n";

  m_object_.Render(camera_);
}

}
