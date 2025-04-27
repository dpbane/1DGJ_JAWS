#include "stdafx.h"
#include "background.h"

#include "game/reference.h"

namespace game {
Background::Background(graphic::Handle handle) : handle_(handle) {
}
void Background::Render(const Camera2D& camera) const {
  const auto texture = ref::MGraphic.GetTexture(graphic::Handle::Background3);
  texture.draw(Point(0, 0));
}


}
