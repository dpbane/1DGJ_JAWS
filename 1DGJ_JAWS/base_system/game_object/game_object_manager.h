#pragma once

#include "game_object.h"
#include "object_handle.h"

namespace base {

class GameObjectManager {
public:
  GameObjectManager();

  void Update();
  void Render(const Camera2D& camera) const;

  ObjectHandle Add(std::unique_ptr<GameObject> object);  // シーン初期化時などに使う
  ObjectHandle AddDynamic(std::unique_ptr<GameObject> object);  // Updateループ内で動的にオブジェクトを増やすときに使う。作成したオブジェクトのSetup, Updateまで実行される。
  bool Kill(const ObjectHandle& handle);  // オブジェクトを削除する
  GameObject* Get(const ObjectHandle& handle) const;  // オブジェクトを取得する

  Array<GameObject*> Find(int tag) const;

  template<typename T>
  Optional<T*> GetAs(const ObjectHandle& handle) const {
    auto obj = Get(handle);
    if (not obj) return std::nullopt;
    return dynamic_cast<T*>(obj.value());
  }

private:
  bool ValidHandle(const ObjectHandle& handle) const;

private:
  Array<std::unique_ptr<GameObject>> game_object_;
  Array<uint32> generation_;
  uint32 current_minimum_index_ = 0;  // 探索の手間を省くため

};

}
