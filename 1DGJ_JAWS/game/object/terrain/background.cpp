#include "stdafx.h"
#include "background.h"

#include "game/reference.h"

namespace game {
Background::Background(graphic::Handle handle) : handle_(handle) {
}
void Background::Render(const Camera2D& camera) const {
  const auto texture = ref::MGraphic.GetTexture(handle_);
  texture.draw(Point(0, 0));
}


}
