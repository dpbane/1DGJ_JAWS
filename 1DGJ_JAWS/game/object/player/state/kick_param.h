#pragma once

namespace game {

constexpr double kKickStartup = 0.1;
constexpr double kKickActive = 0.1 + kKickStartup;
constexpr double kKickRecovery = 0.4 + kKickActive;
constexpr int kKickDamage = 7;
constexpr Rect kKickBoxAct { -120, -10, 120, 65 };
constexpr Rect kKickBoxRecv { -80, -10, 80, 65 };

}
