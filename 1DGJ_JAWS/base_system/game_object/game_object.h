#pragma once

#include "object_handle.h"

namespace base {

class GameObjectManager;

class GameObject abstract {
public:
  virtual ~GameObject() = default;

  void SetHandle(GameObjectManager* GetManager, const ObjectHandle& handle) {
    gom_ = GetManager;
    handle_ = handle;
  }

  virtual void Setup() = 0;
  virtual bool Update() = 0;
  virtual void Render() const = 0;
  virtual void Release() = 0;

  virtual Optional<int> UpdateOrder() const = 0;  // Updateを実行する順序に影響。小さいほど先に実行
  virtual Optional<int> RenderOrder() const = 0;  // 上に同じ
  virtual Optional<int> Tag() const = 0;

protected:
  GameObjectManager* gom_ { nullptr };
  ObjectHandle handle_ { 0, 0 };

};

}
