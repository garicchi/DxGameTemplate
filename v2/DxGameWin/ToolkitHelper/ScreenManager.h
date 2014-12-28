#pragma once

#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "ScreenBase.h"
#include "ToolkitHelper\GameInput.h"

using namespace std;
using namespace DX;

namespace ToolkitHelper{

	class ScreenManager{
	public:
		ScreenManager(const shared_ptr<DeviceResources>& deviceResources, ScreenBase* currentScreen);

		void CreateResources();
		void WindowSizeChanged();
		void ReleaseResources();
		void Update(const StepTimer& timer,const GameInput& input);
		void Render();

	protected:
		shared_ptr<DeviceResources> m_deviceResources;
		ScreenBase* m_currentScreen;

		bool m_isScreenTranslate;
	};

}