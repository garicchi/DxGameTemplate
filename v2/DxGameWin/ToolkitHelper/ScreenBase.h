#pragma once
#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "ToolkitHelper\GameInput.h"
#include "GameObject.h"
#include <vector>
#include "pch.h"

using namespace std;
using namespace DX;

namespace ToolkitHelper{

	class ScreenBase{
	public:
		ScreenBase(const shared_ptr<DeviceResources>& deviceResources);
		virtual void CreateResources();
		virtual void WindowSizeChanged();
		virtual void ReleaseResources();
		virtual ScreenBase* Update(const StepTimer& timer,const GameInput& input);
		virtual void Render();

		virtual void AddObject(shared_ptr<GameObject> obj);
		virtual bool RemoveObject(shared_ptr<GameObject> obj);

	protected:
		shared_ptr<DeviceResources> m_deviceResources;
		vector<shared_ptr<GameObject>> m_renderObjects;
	};

}