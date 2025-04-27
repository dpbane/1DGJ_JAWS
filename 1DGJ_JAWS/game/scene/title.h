#pragma once
#pragma once

#include "game/reference.h"

#include "scene_enum.h"
#include "game/object/ui/ui_button_start.h"
//#include "game/object/ui/ui_button_end.h"
//#include "game/object/ui/ui_button_config.h"

#include "game/object/effect/title_image.h"

namespace scene {

class Title : public SceneManager<SceneEnum>::Scene {
public:
  Title(const InitData& init);

  void update() override;
  void draw() const override;

private:
  base::GameObjectManager m_object_;
  Camera2D camera_ { Vec2{ 0, 0 }, 1.0, CameraControl::None_ };

  base::ObjectHandle fade_handle_;
  //AudioAsset titleAudio;
};
}
