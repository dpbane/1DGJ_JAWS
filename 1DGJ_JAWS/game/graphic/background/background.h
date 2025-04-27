#pragma once

#include "base_system/game_object/game_object.h"
#include "game/graphic/graphic_enum.h"
#include "game/reference.h"

namespace graphic {

class BackGround : public base::GameObject {
public:
  BackGround(int level) {
    _level = level;
  }
  ~BackGround() override = default;


  void Setup() override {}
  bool Update() override {
    return true;
  }

  void Render(const Camera2D& camera) const override {
    // とりあえず雑にゆっくり動かし
    ref::MGraphic.GetTexture(levelList[_level - 1]).draw(10 - ((camera.getCenter().x) / 10), 0);
  }

  void Release() override {}

  Optional<int> UpdateOrder() const override { return 0; }
  Optional<int> RenderOrder() const override { return -100; }
  Optional<int> Tag() const override { return 1; }

private:
  int _level = 0;
  graphic::Handle levelList[2] = { graphic::Handle::Level1, graphic::Handle::Level2 };
};
} // namespace game
