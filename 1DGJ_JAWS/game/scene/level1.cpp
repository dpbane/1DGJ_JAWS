#include "stdafx.h"
#include "level1.h"

#include "game/object/ui/ui_master.h"

#include "game/object/enemy/dummy.h"

namespace scene {

Level1::Level1(const InitData& init) : IScene { init } {
  const auto terrain_handle = m_object_.Add(std::make_unique<game::Terrain>(U"resource/map/level1.csv", graphic::Handle::MapChip1));
  terrain_ = m_object_.GetAs<game::Terrain>(terrain_handle).value();

  const auto player_hanlde = m_object_.Add(std::make_unique<game::Player>(terrain_, Vec2(100, 100)));
  player_ = m_object_.GetAs<game::Player>(player_hanlde).value();

  m_object_.Add(std::make_unique<game::UiMaster>(player_));

  m_object_.Add(std::make_unique<game::DummyEnemy>(terrain_, Vec2(200, 400)));
}

void Level1::update() {
  m_object_.Update();

  camera_.update();
  camera_.setCenter(Vec2 { player_->GetPosition().x, Scene::Height() / 2 });
}

void Level1::draw() const {
  ClearPrint();
  Print << Profiler::FPS() << U" FPS\n";

  m_object_.Render(camera_);



}


}
