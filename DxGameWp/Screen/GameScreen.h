#pragma once

#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "DXTKHelper/ScreenBase.h"
#include "DXTKHelper\GameInput.h"

using namespace std;
using namespace DX;
using namespace DXTKHelper;

class GameScreen :public ScreenBase{
public:
	GameScreen(const shared_ptr<DeviceResources>& deviceResources);

	void CreateResources();
	void ReleaseResources();
	ScreenBase* Update(StepTimer const& timer, const GameInput& input);
	void Render();


};