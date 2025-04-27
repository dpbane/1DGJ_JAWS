#pragma once

#include "game/reference.h"

#include "scene_enum.h"

#include "game/object/player/player.h"

namespace scene {

class Level1 : public SceneManager<SceneEnum>::Scene {
public:

  Level1(const InitData& init) : IScene { init } {
    player_ = m_object_.Add(std::make_unique<game::Player>(Vec2(100, 100)));
  }

  void update() override {
    Optional<game::Player*> player = m_object_.GetAs<game::Player>(player_);
    //camera_.setTargetCenter(Vec2(player.value()->GetPosition().x, 480));
    //camera_.setTargetCenter(Vec2 (m_object_.GetAs<Player>(player_).value().x, 480));

    m_object_.Update();

    camera_.update();
  }

  void draw() const override {
    m_object_.Render(camera_);

    ClearPrint();
    Print << Profiler::FPS() << U" FPS\n";
  }

  base::ObjectHandle player_;
  base::GameObjectManager m_object_;
  Camera2D camera_ { Vec2{ 0, 0 }, 1.0, CameraControl::None_ };
};

}
