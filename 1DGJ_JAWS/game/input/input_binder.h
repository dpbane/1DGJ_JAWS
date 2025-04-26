#pragma once

#include "input_enum.h"

namespace input {

class InputBinder {
public:
  static HashTable<Action, InputGroup> Make();
};

}
