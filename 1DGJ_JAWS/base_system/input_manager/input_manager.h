#pragma once

#include "base_system/pattern/singleton.h"

namespace base {

template<typename Enum>
class InputManager : public pattern::Singleton<InputManager<Enum>> {
public:
  friend class pattern::Singleton<InputManager>;

private:
  InputManager() = default;
  ~InputManager() override = default;

public:
  void Bind(const HashTable<Enum, InputGroup> &bind_map) { bind_map_ = bind_map; }

  bool Down(Enum e) const { return bind_map_.contains(e) ? bind_map_.at(e).down() : false; }
  bool Pressed(Enum e) const { return bind_map_.contains(e) ? bind_map_.at(e).pressed() : false; }

private:
  HashTable<Enum, InputGroup> bind_map_;
};

}
