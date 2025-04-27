#pragma once

#include "base_system/game_object/game_object.h"
#include "game/object/enemy/enemy_base.h"

namespace game {

class Player : public base::GameObject, public EnemyBase {
public:
  enum class StateEnum {
    Stand,
    Walk,
    Air,
    Guard,
    StepFront,
    StepBack,
    PunchGround,
    PunchAir,
    KickGround,
    KickAir
  };

  class State abstract {
  public:
    virtual ~State() = default;
    virtual Optional<StateEnum> Transition(Player& player) = 0;
    virtual void Update(Player& player) = 0;
  };

  template<StateEnum S>
  class StateImpl : public State {
  public:
    ~StateImpl() override = default;
    Optional<StateEnum> Transition(Player& player) override;
    void Update(Player& player) override;
  };

public:
  Player(Terrain* terrain, const Vec2& position);
  ~Player() = default;

  void Setup() override;
  bool Update() override;
  void Render(const Camera2D& camera) const override;
  void Release() override;

  bool OnHpZero() override { return true; }

  Optional<int> UpdateOrder() const override { return 100; }
  Optional<int> RenderOrder() const override { return 100; }
  Optional<int> Tag() const override { return 100; }

  int GetHp() const { return hp_; }
  int GetMaxHp() const { return max_hp_; }

  Vec2 GetPosition() const { return position_; }

private:
  void SetState(StateEnum s);
  void GravityProcess();
  void DoJump();

private:
  HashTable<StateEnum, std::unique_ptr<State>> state_map_;
  StateEnum state_;
  int max_hp_ { 8 };

};


}
