#pragma once

#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "DXTKHelper\GameInput.h"
#include "DXTKHelper/ScreenBase.h"

#include "Audio.h"

using namespace std;
using namespace DX;
using namespace DirectX;
using namespace DXTKHelper;

class SoundScreen :public ScreenBase{
public:
	SoundScreen(const shared_ptr<DeviceResources>& deviceResources);

	void CreateResources();
	void ReleaseResources();
	ScreenBase* Update(StepTimer const& timer, const GameInput& input);
	void Render();

	shared_ptr<AudioEngine> m_audioEngine;
	shared_ptr<SoundEffect> m_soundEffect;
	shared_ptr<SoundEffectInstance> m_effectInstance;
};