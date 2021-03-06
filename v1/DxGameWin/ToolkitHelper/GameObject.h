#pragma once
#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "pch.h"

using namespace std;
using namespace DX;

namespace ToolkitHelper{

	class GameObject{
	public:
		GameObject(const shared_ptr<DeviceResources>& deviceResources)
			:m_deviceResources(deviceResources){
		}
		virtual void CreateResources() = 0;
		virtual void ReleaseResources() = 0;
		virtual void Update(const StepTimer& timer,const GameInput& input) = 0;
		virtual void Render() = 0;

	protected:
		shared_ptr<DeviceResources> m_deviceResources;

	};
}