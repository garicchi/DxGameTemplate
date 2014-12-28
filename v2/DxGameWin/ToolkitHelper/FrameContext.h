#pragma once

#include "pch.h"

#include "Common\StepTimer.h"
#include "ToolkitHelper\GameInput.h"

using namespace DX;

namespace ToolkitHelper{

	class FrameContext{
	public:
		FrameContext(
			StepTimer& timer,
			GameInput& input) :
			m_timer(timer), m_input(input){

		}

		StepTimer& m_timer;
		GameInput& m_input;

	};

}