#pragma once

#include "base_system/game_object/game_object.h"

namespace game {

class TestObject2 : public base::GameObject {
public:
  TestObject2(const Vec2& position, const Vec2& velocity) : position_(position), velocity_(velocity) {}
  ~TestObject2() override = default;


  void Setup() override {}
  void Update() override {
    position_ += velocity_ * Scene::DeltaTime();
  }
  void Render() const override {
    Circle(position_, 10).draw(Palette::Blue);
  }
  void Release() override {}

  Optional<int> UpdateOrder() const override { return 10; }
  Optional<int> RenderOrder() const override { return 0; }
  Optional<int> Tag() const override { return 0; }

private:
  Vec2 position_;
  Vec2 velocity_;
};
} // namespace game
