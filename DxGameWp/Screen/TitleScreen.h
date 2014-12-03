#pragma once

#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "DXTKHelper\GameInput.h"
#include "DXTKHelper/ScreenBase.h"
#include "Renderer/TextureRenderer.h"

using namespace std;
using namespace DX;
using namespace DXTKHelper;

class TitleScreen:public ScreenBase{
public:
	TitleScreen(const shared_ptr<DeviceResources>& deviceResources);

	void CreateResources();
	void ReleaseResources();
	ScreenBase* Update(StepTimer const& timer, const GameInput& input);
	void Render();
private:
	shared_ptr<TextureRenderer> texture1;
};