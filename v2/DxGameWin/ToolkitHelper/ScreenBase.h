#pragma once
#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "ToolkitHelper\GameInput.h"
#include "GameObject.h"
#include <vector>
#include "pch.h"
#include "ToolkitHelper\GameContext.h"
#include "ToolkitHelper\FrameContext.h"

using namespace std;
using namespace DX;

namespace ToolkitHelper{

	class ScreenBase{
	public:
		ScreenBase(const shared_ptr<GameContext>& gameContext);
		virtual void CreateResources();
		virtual void WindowSizeChanged();
		virtual void ReleaseResources();
		virtual ScreenBase* Update(shared_ptr<FrameContext>& frameContext);
		virtual void Render();

		virtual void AddObject(shared_ptr<GameObject> obj);
		virtual bool RemoveObject(shared_ptr<GameObject> obj);

	protected:
		shared_ptr<GameContext> m_gameContext;
		vector<shared_ptr<GameObject>> m_renderObjects;
	};

}