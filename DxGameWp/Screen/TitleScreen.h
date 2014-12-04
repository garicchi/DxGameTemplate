#pragma once

#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "ToolkitHelper\GameInput.h"
#include "ToolkitHelper/ScreenBase.h"
#include "Content/TextureRenderer.h"
#include "Content\SoundObject.h"

using namespace std;
using namespace DX;
using namespace ToolkitHelper;

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