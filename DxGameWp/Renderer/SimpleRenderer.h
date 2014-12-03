#pragma once

#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "DXTKHelper\GameInput.h"
#include "DXTKHelper/RendererBase.h"


using namespace std;
using namespace DX;
using namespace DXTKHelper;

class SimpleRenderer:public RendererBase{
public:
	SimpleRenderer(const shared_ptr<DeviceResources>& deviceResources);

	void CreateResources();
	void ReleaseResources();
	void Update(StepTimer const& timer, const GameInput& input);
	void Render();

};