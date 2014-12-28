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
	SimpleRenderer(const shared_ptr<DeviceResources>& deviceResources);

	void CreateResources();
	void WindowSizeChanged();
	void ReleaseResources();
	void Update(const StepTimer& timer, const GameInput& input);
	void Render();

};