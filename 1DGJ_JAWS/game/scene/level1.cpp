#include "stdafx.h"
#include "level1.h"

#include "game/object/ui/ui_master.h"

#include "game/object/enemy/dummy.h"
#include "game/object/terrain/background.h"
#include "game/object/enemy/ninja.h"
#include "game/object/effect/fade.h"

namespace scene {

Level1::Level1(const InitData& init) : IScene { init } {
  const auto terrain_handle = m_object_.Add(std::make_unique<game::Terrain>(U"resource/map/level1.csv", graphic::Handle::MapChip3, -18));
  terrain_ = m_object_.GetAs<game::Terrain>(terrain_handle).value();

  const auto player_hanlde = m_object_.Add(std::make_unique<game::Player>(terrain_, Vec2(720, 576)));
  player_ = m_object_.GetAs<game::Player>(player_hanlde).value();

  const auto boss_handle = m_object_.Add(std::make_unique<game::Ninja>(terrain_, Vec2(1000, 576)));
  boss_ = m_object_.GetAs<game::EnemyBase>(player_hanlde).value();

  m_object_.Add(std::make_unique<game::UiMaster>(player_, boss_));

  m_object_.Add(std::make_unique<game::Background>(graphic::Handle::Background3));
  //m_object_.Add(std::make_unique<game::DummyEnemy>(terrain_, Vec2(690, 400)));

  fade_handle_ = m_object_.Add(std::make_unique<game::Fade>());
  game::Fade* fade = m_object_.GetAs<game::Fade>(fade_handle_).value();
  fade->SetFadeWhite(0.5);
}

void Level1::update() {
  m_object_.Update();

  camera_.update();
  camera_.setCenter(Vec2 { std::max(720.0, player_->GetPosition().x), Scene::Height() / 2 });
}

void Level1::draw() const {
  ClearPrint();
  Print << Profiler::FPS() << U" FPS\n";

  m_object_.Render(camera_);



}


}
