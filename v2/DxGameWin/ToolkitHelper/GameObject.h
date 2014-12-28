#pragma once
#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "pch.h"
#include "ToolkitHelper\GameContext.h"
#include "ToolkitHelper\FrameContext.h"

using namespace std;
using namespace DX;

namespace ToolkitHelper{

	class GameObject{
	public:
		GameObject(const shared_ptr<GameContext>& gameContext)
			:m_gameContext(gameContext){
		}
		virtual void CreateResources() = 0;
		virtual void WindowSizeChanged() = 0;
		virtual void ReleaseResources() = 0;
		virtual void Update(shared_ptr<FrameContext>& frameContext) = 0;
		virtual void Render() = 0;

	protected:
		shared_ptr<GameContext> m_gameContext;

	};
}