#pragma once

namespace game {

constexpr double kPunchStartup = 0.05;
constexpr double kPunchActive = 0.1 + kPunchStartup;
constexpr double kPunchRecovery = 0.2 + kPunchActive;
constexpr int kPunchDamage = 4;
constexpr Rect kPunchBoxAct { -120, -45, 120, 65 };
constexpr Rect kPunchBoxRecv { -70, -45, 70, 65 };

}
