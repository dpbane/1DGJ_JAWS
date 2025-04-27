#include "stdafx.h"
#include "game.h"

#include "reference.h"

#include "scene/level1.h"

namespace game {

constexpr int32 target_fps = 60;
constexpr int32 window_width = 1280;
constexpr int32 window_height = 720;
const String window_title = U"1DGJ_JAWS";

Game::Game() {
}

void Game::Setup() {
  ref::MWindow.Setup(window_width, window_height, window_title);
  ref::MInput.Bind(input::InputBinder::Make());

  ref::MGraphic.Register(graphic::Handle::Sample, U"resource/image/sample.png");
  ref::MGraphic.Register(graphic::Handle::Itekoma, U"resource/image/itekoma.png");
  ref::MGraphic.RegisterChip(graphic::Handle::Sample, 16, 16, 6);

  ref::MGraphic.Register(graphic::Handle::MapChip1, U"resource/image/mapchip1.png");
  ref::MGraphic.RegisterChip(graphic::Handle::MapChip1, 64, 64, 3);

  ref::MGraphic.Register(graphic::Handle::Rat, U"resource/image/rat.png");

  ref::MAudio.Register(audio::Handle::Sample, U"resource/audio/maou_se_system46.ogg");

  Addon::Register(U"FrameRateLimit", std::make_unique<base::FrameRateLimitAddon>(target_fps));

  scene_manager_.add<scene::Level1>(scene::SceneEnum::Level1);
  scene_manager_.init(scene::SceneEnum::Level1, 0.02s);
}

bool Game::Process() {
  return scene_manager_.update();
}


}
