# include <Siv3D.hpp> // Siv3D v0.6.16

#include "game/game.h"

void Main() {

  game::Game gm;
  gm.Setup();

  while (System::Update() && gm.Process()) {
  }


}
