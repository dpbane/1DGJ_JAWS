#include "stdafx.h"
#include "title.h"

#include "game/reference.h"
#include "game/object/terrain/background.h"
#include "game/object/effect/fade.h"

namespace scene {
Title::Title(const InitData& init) : IScene { init } {
  // タイトルロゴ
  m_object_.Add(std::make_unique<game::TitleImage>(Vec2 { 640,200 })); // あとで画像差し替えしたい

  // button
  m_object_.Add(std::make_unique<game::UiButtonStart>(Rect(Arg::center(0, 100), 700, 80))); // Start
  //m_object_.Add(std::make_unique<game::UiButtonConfig>(Rect(Arg::center(0, 100), 300, 80))); // Config
  //m_object_.Add(std::make_unique<game::UiButtonEnd>(Rect(Arg::center(0, 200), 300, 80))); // End

  m_object_.Add(std::make_unique<game::Background>(graphic::Handle::Background2));

  fade_handle_ = m_object_.Add(std::make_unique<game::Fade>());
  game::Fade* fade = m_object_.GetAs<game::Fade>(fade_handle_).value();
  fade->SetWhite();

  // タイトル曲
  ref::MAudio.GetAudio(audio::Handle::Title).play();
  ref::MAudio.GetAudio(audio::Handle::Title).setVolume(0.5);
}

void Title::update() {

  game::Fade* fade = m_object_.GetAs<game::Fade>(fade_handle_).value();

  m_object_.Update();
  if (KeySpace.pressed()) {
    // Stage1 開始
    // とりまSpace
    // 
    ref::MAudio.GetAudio(audio::Handle::Title).fadeVolume(0.0, 1s);

    fade->SetFadeBlack(0.5);
  }

  if (fade->IsBlack()) {
    changeScene(scene::SceneEnum::Level1, 0);
  }
}

void Title::draw() const {
  ClearPrint();
  Print << Profiler::FPS() << U" FPS\n";

  m_object_.Render(camera_);
}

}
