#include "stdafx.h"
#include "terrain.h"

namespace game {
Terrain::Terrain() {
}
void Terrain::Setup() {
}

bool Terrain::Update() {
  return true;
}

void Terrain::Render(const Camera2D& camera) const {
  const auto t = camera.createTransformer();
  const Rect dummy(0, 500, Scene::Width(), 100);
  dummy.draw(ColorF(0.5, 0.5, 0.7));
}

void Terrain::Release() {
}

bool Terrain::Conflict(const Rect& box) const {
  const Rect dummy(0, 500, Scene::Width(), 100);
  return box.intersects(dummy);
}




}
