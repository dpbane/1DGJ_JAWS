#pragma once

namespace audio {

enum class Handle : uint8_t {
  Sample = 0,
  Title,      // タイトル画面
  Way1,       // 道中1
  Way3,       // 道中3
  Boss1,      // ボス1
  Boss2,      // ボス2
  Ending      // エンディング
};


}
