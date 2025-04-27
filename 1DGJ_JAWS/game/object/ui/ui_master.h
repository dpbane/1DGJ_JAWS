#pragma once

#include "base_system/game_object/game_object.h"
#include "game/object/player/player.h"

namespace game {

class UiMaster : public base::GameObject {
public:
  UiMaster(Player* player);
  ~UiMaster() override;

  void Setup() override;
  bool Update() override;
  void Render(const Camera2D& camera) const override;
  void Release() override;

  Optional<int> UpdateOrder() const override { return 10000; }
  Optional<int> RenderOrder() const override { return 10000; }
  Optional<int> Tag() const override { return 0; }

private:
  Player* player_;
};


}
