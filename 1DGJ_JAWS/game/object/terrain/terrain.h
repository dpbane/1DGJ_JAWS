#pragma once

#include "base_system/game_object/game_object.h"
#include "game/graphic/graphic_enum.h"

namespace game {

class Terrain : public base::GameObject {
public:
  Terrain(const FilePath& path_csv, graphic::Handle ghandle, int y_offset = 0);
  ~Terrain() override = default;

  void Setup();
  bool Update();
  void Render(const Camera2D& camera) const;  // <-- この中ですべての描画を済ませる
  void Release();

  Optional<int> UpdateOrder() const { return none; }
  Optional<int> RenderOrder() const { return 10; }  // 小さい数字にセット
  Optional<int> Tag() const { return 0; }

  bool Conflict(const Rect& box) const;
  double NearestX(double x) const;  // 指定したX座標から最も近いチップの境目の座標を得る
  double NearestY(double y) const;  // 指定したX座標から最も近いチップの境目の座標を得る

private:
  int GetChip(int x, int y) const;
  bool IsWall(int index) const;

private:
  const FilePath path_csv_;
  const graphic::Handle ghandle_;
  const int y_offset_;

  size_t y_count_ {};
  size_t x_count_ {};

  Grid<int32> map_ {};

};

}
