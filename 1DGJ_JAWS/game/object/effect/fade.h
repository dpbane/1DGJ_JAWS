#pragma once

#include "base_system/game_object/game_object.h"

namespace game {

class Fade : public base::GameObject {
public:
  Fade();
  ~Fade() override = default;

  bool Update() override;
  void Setup() override {}
  void Render(const Camera2D& camera) const override;
  void Release() override {}

  Optional<int> UpdateOrder() const override { return 20000; }  // 要調整
  Optional<int> RenderOrder() const override { return 20000; } // 要調整
  Optional<int> Tag() const override { return 100; }

  void SetFadeBlack(double time);
  void SetFadeWhite(double time);
  void SetWhite();

  bool IsBlack() const { return alpha_ == 1.0; }
  bool IsWhite() const { return alpha_ == 0.0; }

private:
  double alpha_ { 0 };

  double fade_time_inv_ { 1 };
  bool to_black_ { false };


};

}
