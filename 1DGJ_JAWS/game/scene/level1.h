#pragma once

#include "game/reference.h"

#include "scene_enum.h"

#include "game/object/player/player.h"

namespace scene {

class Level1 : public SceneManager<SceneEnum>::Scene {
public:

  Level1(const InitData& init) : IScene { init } {
    m_object_.Add(std::make_unique<game::Player>(Vec2(100, 100)));
  }

  void update() override {
    m_object_.Update();

    camera_.update();
  }

  void draw() const override {
    m_object_.Render(camera_);

    ClearPrint();
    Print << Profiler::FPS() << U" FPS\n";
  }


  base::GameObjectManager m_object_;
  Camera2D camera_ { Vec2{ 0, 0 }, 1.0, CameraControl::None_ };
};

}
