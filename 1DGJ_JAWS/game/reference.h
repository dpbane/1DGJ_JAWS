#pragma once

#include "base_system/frame_rate_limit/frame_rate_limit.h"
#include "base_system/input_manager/input_manager.h"
#include "base_system/window_manager/window_manager.h"

#include "graphic/graphic_enum.h"
#include "base_system/graphic_manager/graphic_manager.h"

#include "audio/audio_enum.h"
#include "base_system/audio_manager/audio_manager.h"

#include "input/input_binder.h"

#include "base_system/game_object/game_object_manager.h"

namespace ref {

inline static base::InputManager<input::Action>& MInput = base::InputManager<input::Action>::Instance();
inline static base::WindowManager& MWindow = base::WindowManager::Instance();
inline static base::GraphicManager<graphic::Handle>& MGraphic = base::GraphicManager<graphic::Handle>::Instance();
inline static base::AudioManager<audio::Handle>& MAudio = base::AudioManager<audio::Handle>::Instance();


}
