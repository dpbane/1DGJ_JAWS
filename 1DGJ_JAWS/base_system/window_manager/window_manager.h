#pragma once

#include "base_system/pattern/singleton.h"

namespace base {

class WindowManager : public pattern::Singleton<WindowManager> {
public:
  friend class pattern::Singleton<WindowManager>;

private:
  WindowManager() = default;
  ~WindowManager() override = default;

public:
  void Setup(int width, int height, const String& title, TextureFilter filter = TextureFilter::Linear);

};

}
