#include "stdafx.h"
#include "input_binder.h"

namespace input {

HashTable<Action, InputGroup> InputBinder::Make() {
  HashTable<Action, InputGroup> ret;
  ret.insert({ Action::Left, KeyLeft | KeyA });
  ret.insert({ Action::Right, KeyRight | KeyD });
  ret.insert({ Action::Up, KeyUp | KeyW });
  ret.insert({ Action::Down, KeyDown | KeyS });
  ret.insert({ Action::Confirm, KeyEnter | KeySpace });
  ret.insert({ Action::Cancel, KeyEscape | KeyBackspace });
  return ret;
}

}
