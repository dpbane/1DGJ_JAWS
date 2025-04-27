#pragma once

namespace game {

class EnemyBase {
public:
  virtual ~EnemyBase() = default;

  bool EnemyPreUpdate() {
    bool ret { true };
    if (hp_ <= 0 && previous_hp_ > 0) ret = OnHpZero();
    previous_hp_ = hp_;
    return ret;
  }

  bool EnemyPostUpdate() {
    position_ += velocity_ * Scene::DeltaTime();
  }

  virtual bool OnHpZero() = 0;

  void TakeDamage(int damage) {
    hp_ = std::max(hp_ - damage, 0);
  }

  void RenderHitbox() const;

protected:
  Vec2 position_ {};
  Vec2 velocity_ { 0, 0 };
  int previous_hp_ = 0, hp_ = 0;
  int atk_power_ = 0;
  Array<Rect> hitbox_ {};  // オブジェクトのくらい判定
  Array<Rect> attackbox_ {};  // オブジェクトの攻撃判定
  Rect terrainbox_;  // 地形判定用
};



}
