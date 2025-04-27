#pragma once

#include "base_system/game_object/game_object.h"

namespace game {

class TestObject1 : public base::GameObject {
public:
  TestObject1(const Vec2& position,
              const Vec2& velocity) : position_(position), velocity_(velocity) {
  }
  ~TestObject1() override = default;


  void Setup() override {}
  bool Update() override {
    position_ += velocity_ * Scene::DeltaTime();

    if (position_.x > 200) {
      gom_->AddDynamic(std::make_unique<TestObject1>(position_ + Vec2 { -100, 100 }, velocity_));
      gom_->AddDynamic(std::make_unique<TestObject1>(position_ + Vec2 { -140, 120 }, velocity_));
      return false;
    }

    return true;
  }
  void Render() const override {
    Circle(position_, 10).draw(Palette::Red);
  }
  void Release() override {}

  Optional<int> UpdateOrder() const override { return 0; }
  Optional<int> RenderOrder() const override { return 10; }
  Optional<int> Tag() const override { return 1; }

private:
  Vec2 position_;
  Vec2 velocity_;
};
} // namespace game
