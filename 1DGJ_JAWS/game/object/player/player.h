#pragma once

#include "base_system/game_object/game_object.h"
#include "game/object/enemy/enemy_base.h"
#include "game/object/object_tag.h"

namespace game {

class Player : public EnemyBase {
public:
  enum class StateEnum {
    Stand,
    Walk,
    Air,
    Step,
    PunchGround,
    PunchAir,
    KickGround,
    KickAir,
    Knockback,
    Death
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
  void Render(const Camera2D& camera) const override;
  void Release() override;

  bool MainUpdate() override;
  bool OnHpZero() override { return true; }

  Optional<int> UpdateOrder() const override { return 100; }
  Optional<int> RenderOrder() const override { return 100; }
  Optional<int> Tag() const override { return (int)(ObjectTag::Player); }

  int GetHp() const { return hp_; }
  int GetMaxHp() const { return max_hp_; }

  Vec2 GetPosition() const { return position_; }

private:
  void SetState(StateEnum s);
  void GravityProcess();
  void EnemyInteractProcess();
  void InvinsibleProcess();
  bool HitAgainst(EnemyBase* enemy);
  bool TakeAgainst(EnemyBase* enemy);

  void DoJump();
  void DoKnockback(EnemyBase* enemy);
  void DoPunch();
  void DoKick();
  void DoStep();

private:
  HashTable<StateEnum, std::unique_ptr<State>> state_map_;
  StateEnum state_;
  int max_hp_ { 8 };
  double invinsible_time_ { 0.0 };  // 無敵時間。0より大きいと有効
  double knockback_land_time_ { 0.0 };  // 吹き飛び後、着地したらこの数値を0より大きくする。0になったら行動可能に

  double motion_time_ { 0.0 };  // パンチ、キック、ステップの各モーション経過時間

  int frame_index_ { 0 };  // 描画する画像ID

  HashSet<EnemyBase*> attack_enemy_set_;

};


}
