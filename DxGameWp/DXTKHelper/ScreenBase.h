#pragma once
#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "DXTKHelper\GameInput.h"
#include "RendererBase.h"
#include <vector>
#include "pch.h"

using namespace std;
using namespace DX;

namespace DXTKHelper{

	class ScreenBase{
	public:
		ScreenBase(const shared_ptr<DeviceResources>& deviceResources);
		virtual void CreateResources();
		virtual void ReleaseResources();
		virtual ScreenBase* Update(StepTimer const& timer,const GameInput& input);
		virtual void Render();

		virtual void AddObject(shared_ptr<RendererBase> obj);
		virtual bool RemoveObject(shared_ptr<RendererBase> obj);

	protected:
		shared_ptr<DeviceResources> m_deviceResources;
		vector<shared_ptr<RendererBase>> m_renderObjects;
	};

}