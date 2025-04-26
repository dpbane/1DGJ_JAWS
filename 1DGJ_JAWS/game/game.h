#pragma once

#include "scene/scene_enum.h"

namespace game {

class Game {
public:
  Game();

  void Setup();
  bool Process();

private:
  SceneManager<scene::SceneEnum> scene_manager_;
};




}
