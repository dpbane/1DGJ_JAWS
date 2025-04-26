#pragma once

#include "game/reference.h"

#include "scene_enum.h"

#include "game/object/test_object_1.h"
#include "game/object/test_object_2.h"

namespace scene {

class Test : public SceneManager<SceneEnum>::Scene {
public:

  Test(const InitData& init) : IScene { init } {
    m_object_.Add(std::make_unique<game::TestObject1>(Vec2(100, 100), Vec2(100, 0)));
    m_object_.Add(std::make_unique<game::TestObject2>(Vec2(100, 150), Vec2(100, 0)));
  }

  void update() override {
    m_object_.Update();
  }

  void draw() const override {
    static int index = 0;
    ++index;

    ref::MGraphic.GetTexture(graphic::Handle::Sample).draw(50, 50);
    ref::MGraphic.GetTextureRegion(graphic::Handle::Sample, (index / 10) % 12).draw(200, 50);

    if (index % 120 == 0) ref::MAudio.GetAudio(audio::Handle::Sample).playOneShot(0.5);

    ClearPrint();
    Print << Profiler::FPS() << U" FPS\n";

    m_object_.Render();
  }

  base::GameObjectManager m_object_;
};

}
