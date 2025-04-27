#pragma once

#include "game/reference.h"

#include "scene_enum.h"

#include "game/object/player/player.h"
#include "game/object/terrain/terrain.h"

namespace scene {

class Level1 : public SceneManager<SceneEnum>::Scene {
public:
  Level1(const InitData& init);

  void update() override;

  void draw() const override;

private:
  base::GameObjectManager m_object_;
  Camera2D camera_ { Vec2{ 0, 0 }, 1.0, CameraControl::None_ };

  game::Terrain* terrain_;
  game::Player* player_;
};

}
