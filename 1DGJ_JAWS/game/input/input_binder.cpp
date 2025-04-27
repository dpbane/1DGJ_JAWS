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
  ret.insert({ Action::Jump, KeySpace });
  ret.insert({ Action::Skill1, KeyZ });
  ret.insert({ Action::Skill2, KeyX });
  ret.insert({ Action::Skill3, KeyC });
  return ret;
}

}
