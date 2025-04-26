#pragma once

#include "base_system/pattern/singleton.h"

namespace base {

template<typename Enum>
class GraphicManager : public pattern::Singleton<GraphicManager<Enum>> {
private:
  struct ChipData {
    int width, height;
    int x_num;
    Rect MakeRect(int index) const {
      return Rect(
        width * (index % x_num),
        height * (index / x_num),
        width,
        height);
    }
  };

public:
  friend class pattern::Singleton<GraphicManager>;

private:
  GraphicManager() = default;
  ~GraphicManager() override = default;

public:
  void Register(Enum id, const FilePath& path) {
    TextureAsset::Register(GetString(id), path);
  }

  void Register(Enum id, const std::unique_ptr<TextureAssetData> tad) {
    TextureAsset::Register(GetString(id), std::move(tad));
  }

  // 対応する画像データが、同じサイズの画像の繰り返しデータであることを登録する
  void RegisterChip(Enum id, int width, int height, int x_num) {
    chip_table_.insert({ id, ChipData{
      .width = width,
      .height = height,
      .x_num = x_num }
      });
  }

  Texture GetTexture(Enum id) const {
    return TextureAsset(GetString(id));
  }

  // 繰り返しデータの一つを取得する
  TextureRegion GetTextureRegion(Enum id, int index) const {
    if (index < 0) return Texture();
    if (not chip_table_.contains(id)) return Texture();
    const ChipData& chip = chip_table_.at(id);
    Texture texture = GetTexture(id);
    return texture(chip.MakeRect(index));
  }

private:
  String GetString(Enum id) const {
    return U"{:}"_fmt(static_cast<int>(id));
  }

private:
  HashTable<Enum, ChipData> chip_table_;


};

}
