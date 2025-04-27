#include "stdafx.h"
#include "game_object_manager.h"

#include <algorithm>

namespace base {

constexpr size_t kObjReserve = 1024;

GameObjectManager::GameObjectManager() {
  game_object_.reserve(kObjReserve);
  generation_.reserve(kObjReserve);
}

void GameObjectManager::Update() {
  // ループごとにインデックスソート。パフォーマンスが気になるなら動的追加・削除部分でやる

  // まずインデックスの作成
  Array<uint32> index_list;
  index_list.reserve(game_object_.size());
  for (int index = 0; const auto & obj : game_object_) {
    if (obj && obj->UpdateOrder()) index_list.push_back(index);
    index++;
  }

  // インデックスのソート
  std::sort(index_list.begin(), index_list.end(), [this](int a, int b) {
    return game_object_[a]->UpdateOrder() < game_object_[b]->UpdateOrder();
  });

  // 実行
  for (const auto& index : index_list) {
    if (not game_object_[index]->Update()) {
      Kill(ObjectHandle {
        .index = index,
        .generation = generation_[index]
});
    }
  }

}

void GameObjectManager::Render(const Camera2D& camera) const {
  // ループごとにインデックスソート。パフォーマンスが気になるなら動的追加・削除部分でやる

  // まずインデックスの作成
  Array<int> index_list;
  index_list.reserve(game_object_.size());
  for (int index = 0; const auto & obj : game_object_) {
    if (obj && obj->RenderOrder()) index_list.push_back(index);
    index++;
  }

  // インデックスのソート
  std::sort(index_list.begin(), index_list.end(), [this](int a, int b) {
    return game_object_[a]->RenderOrder() < game_object_[b]->RenderOrder();
  });

  // 実行
  for (const auto& index : index_list) {
    game_object_[index]->Render(camera);
  }
}

ObjectHandle GameObjectManager::Add(std::unique_ptr<GameObject> object) {
  // 空いている場所を探す
  auto itr = std::find(game_object_.begin() + current_minimum_index_, game_object_.end(), nullptr);
  if (itr != game_object_.end()) {
    // 空いている場所が見つかった
    const auto index = static_cast<uint32>(std::distance(game_object_.begin(), itr));
    game_object_[index] = std::move(object);
    current_minimum_index_ = index + 1;
    ObjectHandle handle {
      .index = index,
      .generation = generation_[index]
    };
    game_object_[index]->SetHandle(this, handle);
    return handle;
  }

  // 新規作成
  game_object_.push_back(std::move(object));
  generation_.push_back(0);
  current_minimum_index_ = (uint32)(game_object_.size() - 1);
  ObjectHandle handle {
        .index = (uint32)(game_object_.size() - 1),
        .generation = 0
  };
  game_object_[handle.index]->SetHandle(this, handle);
  return handle;
}

ObjectHandle GameObjectManager::AddDynamic(std::unique_ptr<GameObject> object) {
  auto obj = Add(std::move(object));
  Get(obj)->Setup();
  Get(obj)->Update();
  return obj;
}

bool GameObjectManager::Kill(const ObjectHandle& handle) {
  if (not ValidHandle(handle)) return false;

  // 解放処理

  if (current_minimum_index_ > handle.index) current_minimum_index_ = handle.index;
  generation_[handle.index] += 1;
  game_object_[handle.index]->Release();
  game_object_[handle.index].reset();
  return true;
}

GameObject* GameObjectManager::Get(const ObjectHandle& handle) const {
  if (not ValidHandle(handle)) return nullptr;
  return game_object_[handle.index].get();
}

Array<GameObject*> GameObjectManager::Find(int tag) const {
  Array<GameObject*> ret;
  for (const auto& obj : game_object_) {
    if (obj && obj->Tag() == tag) {
      ret.push_back(obj.get());
    }
  }
  return ret;
}

bool GameObjectManager::ValidHandle(const ObjectHandle& handle) const {
  if (handle.index < 0) return false;
  if (handle.index >= game_object_.size()) return false;
  if (generation_[handle.index] != handle.generation) return false;
  return true;
}



}
