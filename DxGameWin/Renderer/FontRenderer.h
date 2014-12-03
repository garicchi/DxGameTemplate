#pragma once

#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "DXTKHelper\GameInput.h"
#include "DXTKHelper/RendererBase.h"

#include"SpriteFont.h"
using namespace std;
using namespace DX;
using namespace DXTKHelper;
using namespace DirectX;

class FontRenderer :public RendererBase{
public:
	FontRenderer(const shared_ptr<DeviceResources>& deviceResources);

	void CreateResources();
	void ReleaseResources();
	void Update(StepTimer const& timer,const GameInput& input);
	void Render();

protected:
	shared_ptr<SpriteFont> m_spriteFont;
	shared_ptr<SpriteBatch> m_spriteBatch;

};