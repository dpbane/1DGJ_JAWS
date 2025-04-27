#include "stdafx.h"
#include "terrain.h"

#include "game/reference.h"

namespace game {

constexpr int kChipSize = 64;

Terrain::Terrain(const FilePath& path_csv, graphic::Handle ghandle) :
  path_csv_(path_csv), ghandle_(ghandle) {
  CSV csv { path_csv_ };
  if (not csv) return;

  // マップのセルの数
  y_count_ = csv.rows();
  x_count_ = csv.columns(0);
  map_ = Grid<int32>(x_count_, y_count_);

  for (size_t y = 0; y < y_count_; ++y) {
    for (size_t x = 0; x < x_count_; ++x) {
      // 指定した行・列の値を読み込む
      map_[y][x] = csv.get<int32>(y, x);
    }
  }
}

void Terrain::Setup() {
}

bool Terrain::Update() {
  return true;
}

void Terrain::Render(const Camera2D& camera) const {

  const auto t = camera.createTransformer();

  const Vec2& center = camera.getCenter();
  const int left_x = (center.x - Scene::Width() / 2) / kChipSize - 1;
  const int right_x = (center.x + Scene::Width() / 2) / kChipSize + 1;
  const int top_y = (center.y - Scene::Height() / 2) / kChipSize - 1;
  const int bottom_y = (center.y + Scene::Height() / 2) / kChipSize + 1;

  // マップ
  for (int32 y = top_y; y <= bottom_y; ++y) {
    for (int32 x = left_x; x <= right_x; ++x) {
      const Point pos { (x * kChipSize), (y * kChipSize) };
      ref::MGraphic.GetTextureRegion(ghandle_, GetChip(x, y)).draw(pos);
    }
  }

}
void Terrain::Release() {
}

bool Terrain::Conflict(const Rect& box) const {
  int left = (box.leftX() + 1) / kChipSize;
  int right = (box.rightX() - 1) / kChipSize;
  int top = (box.topY() + 1) / kChipSize;
  int bottom = (box.bottomY() - 1) / kChipSize;

  for (int x = left; x <= right; ++x) {
    for (int y = top; y <= bottom; ++y) {
      if (IsWall(GetChip(x, y))) return true;
    }
  }

  return false;
}

double Terrain::NearestX(double x) const {
  return std::round(x / kChipSize) * kChipSize;
}

double Terrain::NearestY(double y) const {
  return std::round(y / kChipSize) * kChipSize;
}

int Terrain::GetChip(int x, int y) const {
  if (x < 0) return 0;
  if (x >= x_count_) return 0;
  if (y < 0) return 0;
  if (y >= y_count_) return 0;
  return map_[y][x];
}

bool Terrain::IsWall(int index) const {
  return index != 0;
}




}
