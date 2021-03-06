#pragma once

#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "ToolkitHelper\GameInput.h"
#include "ToolkitHelper/GameObject.h"


using namespace std;
using namespace DX;
using namespace ToolkitHelper;

class SimpleRenderer:public GameObject{
public:
	SimpleRenderer(const shared_ptr<GameContext>& gameContext);

	void CreateResources();
	void WindowSizeChanged();
	void ReleaseResources();
	void Update(shared_ptr<FrameContext>& frameContext);
	void Render();

};