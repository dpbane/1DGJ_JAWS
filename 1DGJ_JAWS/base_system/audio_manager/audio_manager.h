#pragma once

#include "base_system/pattern/singleton.h"

namespace base {

template<typename Enum>
class AudioManager : public pattern::Singleton<AudioManager<Enum>> {
public:
  friend class pattern::Singleton<AudioManager>;

private:
  AudioManager() = default;
  ~AudioManager() override = default;

public:
  void Register(Enum id, const FilePath& path) {
    AudioAsset::Register(GetString(id), path);
  }

  AudioAsset GetAudio(Enum id) const {
    return AudioAsset(GetString(id));
  }

private:
  String GetString(Enum id) const {
    return U"{:}"_fmt(static_cast<int>(id));
  }

};

}
