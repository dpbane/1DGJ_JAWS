#include "stdafx.h"
#include "ui_master.h"


namespace game {

UiMaster::UiMaster(Player* player) : player_(player) {
}

UiMaster::~UiMaster() {
}

void UiMaster::Setup() {
}

bool UiMaster::Update() {
  return true;
}

#pragma warning(suppress : 4100)
void UiMaster::Render(const Camera2D& camera) const {

  constexpr int kMainBoxHeight = 120;
  const auto main_box = Rect(0, Scene::Height() - kMainBoxHeight, Scene::Width(), kMainBoxHeight);
  main_box.draw(ColorF(0.2, 0.2, 0.2)).drawFrame(2.0, ColorF(0.8, 0.8, 0.8));

  for (int k = 0; k < player_->GetMaxHp(); ++k) {
    const auto hp_box = Rect(160, 12, 24, 36).movedBy(k * 30, 0);
    if (k < player_->GetHp()) {
      hp_box.draw(ColorF(0.8, 0.2, 0.2)).drawFrame(2.0, ColorF(0.8, 0.8, 0.8));
    }
    else {
      hp_box.draw(ColorF(0.2, 0.2, 0.2)).drawFrame(2.0, ColorF(0.8, 0.8, 0.8));
    }
  }
}

void UiMaster::Release() {
}










}
