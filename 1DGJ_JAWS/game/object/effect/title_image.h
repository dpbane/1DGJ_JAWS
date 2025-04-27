#pragma once

#include "base_system/game_object/game_object.h"

namespace game {

class TitleImage : public base::GameObject {
public:
  TitleImage(const Vec2& position);
  ~TitleImage() = default;

  void Setup() override;
  bool Update() override;
  void Render(const Camera2D& camera) const override;
  void Release() override;

  Optional<int> UpdateOrder() const override { return 200; } // 一番上くらい
  Optional<int> RenderOrder() const override { return 200; } // 一番上くらい 
  Optional<int> Tag() const override { return 100; }

private:
  Texture texture_;
  Vec2 base_position_ {};
  Vec2 position_ {};
};
}
