#pragma once

#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "ToolkitHelper\GameInput.h"
#include "ToolkitHelper/GameObject.h"
#include "ToolkitHelper\GameContext.h"

#include "Audio.h"

using namespace std;
using namespace DX;
using namespace ToolkitHelper;
using namespace DirectX;
using namespace Platform;

class SoundObject :public GameObject{
public:
	SoundObject(const shared_ptr<GameContext>& gameContext,String^ path);

	void CreateResources();
	void WindowSizeChanged();
	void ReleaseResources();
	void Update(shared_ptr<FrameContext>& frameContext);
	void Render();

	void Play();

	String^ m_path;
	shared_ptr<SoundEffectInstance> m_effectInstance;
protected:
	shared_ptr<AudioEngine> m_audioEngine;
	shared_ptr<SoundEffect> m_soundEffect;
	
};