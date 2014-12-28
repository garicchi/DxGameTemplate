#pragma once

#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "ScreenBase.h"
#include "ToolkitHelper\GameInput.h"
#include "ToolkitHelper\GameContext.h"

using namespace std;
using namespace DX;

namespace ToolkitHelper{

	class ScreenManager{
	public:
		ScreenManager(const shared_ptr<GameContext>& gameContext, ScreenBase* currentScreen);

		void CreateResources();
		void WindowSizeChanged();
		void ReleaseResources();
		void Update(const StepTimer& timer,const GameInput& input);
		void Render();

	protected:
		shared_ptr<GameContext> m_gameContext;
		ScreenBase* m_currentScreen;

		bool m_isScreenTranslate;
	};

}