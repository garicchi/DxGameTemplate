#pragma once
#include "pch.h"
#include "Common\DeviceResources.h"

using namespace DX;
using namespace std;

class GameContext{
public:
	GameContext(
		shared_ptr<DeviceResources>& deviceResources)
	:m_deviceResources(deviceResources){

	}

	shared_ptr<DeviceResources>& m_deviceResources;
};