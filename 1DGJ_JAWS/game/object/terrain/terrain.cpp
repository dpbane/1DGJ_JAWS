#include "stdafx.h"
#include "terrain.h"

namespace game {

constexpr int kChipSize = 50;  // 50は仮の数値。マップチップのサイズに合わせて変更

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

  // マップチップ用テクスチャ
  MapChip mapchip;

  // マップのセルの数
  constexpr Size MapSize { 5, 2 };
  // CSC ファイルを読み込む
  FilePathView path = U"MapChip/Level1/layer1.csv";
  CSV csv { path };

  // 読み込みに失敗したら
  if (not csv)
  {
    // エラー
    throw Error { U"Failed to load `{}`"_fmt(path) };
  }

  // 行数
  const size_t yCount = csv.rows();

  // 1 行目の列数（以降も同じ列数と仮定する）
  const size_t xCount = csv.columns(0);

  // 二次元配列
  Grid<int32> mapLayer0(xCount, yCount);

  for (size_t y = 0; y < yCount; ++y)
  {
    for (size_t x = 0; x < xCount; ++x)
    {
      // 指定した行・列の値を読み込む
      mapLayer0[y][x] = csv.get<int32>(y, x);
    }
  }
  if (mapLayer0.size() != MapSize)
  {
    // MapSize と、ロードしたデータのサイズが一致しない場合のエラー
    throw Error { U"mapLayer0: {}"_fmt(mapLayer0.size()) };
  }
  while (System::Update()) {
    // マップ
    for (int32 y = 0; y < MapSize.y; ++y)
    {
      for (int32 x = 0; x < MapSize.x; ++x)
      {
        // マップチップの描画座標
        const Point pos { (x * MapChip::MapChipSize), (y * MapChip::MapChipSize) };

        // 最下層のマップチップ
        if (const int32 chipIndex = mapLayer0[y][x];
          chipIndex != 0) // 0 の場合は描画しない
        {
          mapchip.get(chipIndex).draw(pos);
        }
      }
    }
  }


}
void Terrain::Release() {
}

bool Terrain::Conflict(const Rect& box) const {
  const Rect dummy(0, 500, Scene::Width(), 100);
  return box.intersects(dummy);
}

double Terrain::NearestX(double x) const {
  return std::round(x / kChipSize) * kChipSize;
}

double Terrain::NearestY(double y) const {
  return std::round(y / kChipSize) * kChipSize;
}




}
