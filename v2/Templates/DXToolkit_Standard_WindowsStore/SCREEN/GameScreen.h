#pragma once

#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "ToolkitHelper/ScreenBase.h"
#include "ToolkitHelper\GameInput.h"
#include "ToolkitHelper\FrameContext.h"

using namespace std;
using namespace DX;
using namespace ToolkitHelper;

class GameScreen :public ScreenBase{
public:
	GameScreen(const shared_ptr<GameContext>& gameContext);

	void CreateResources();
	void WindowSizeChanged();
	void ReleaseResources();
	ScreenBase* Update(shared_ptr<FrameContext>& frameContext);
	void Render();



};