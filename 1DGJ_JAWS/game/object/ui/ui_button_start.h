#pragma once

#include "base_system/game_object/game_object.h"

namespace game {

class UiButtonStart : public base::GameObject {
public:
  UiButtonStart(const Rect& rect);
  ~UiButtonStart() override = default;;

  void Setup() override;
  bool Update() override;
  void Render(const Camera2D& camera) const override;
  void Release() override;

  Optional<int> UpdateOrder() const override { return 200; } // 一番上くらい
  Optional<int> RenderOrder() const override { return 200; } // 一番上くらい 
  Optional<int> Tag() const override { return 100; }

private:
  String text_;
  Rect rect_;
  const Font font { FontMethod::MSDF, 48, Typeface::Bold };

};
}
