#pragma once;
#include "pch.h"
#include "ToolkitHelper\AnimationBase.h"

using namespace ToolkitHelper;

class LinerAnimation :public AnimationBase{
public:
	LinerAnimation(const shared_ptr<GameContext>& gameContext,double from,double to)
	:AnimationBase(gameContext),m_from(from),m_to(to),m_value(from){
		
	}

	void CreateResources(){
		AnimationBase::CreateResources();
	}
	void WindowSizeChanged(){
		AnimationBase::WindowSizeChanged();
	}
	void ReleaseResources(){
		AnimationBase::ReleaseResources();
	}
	void Update(shared_ptr<FrameContext>& frameContext){
		AnimationBase::Update(frameContext);

		m_value = m_from + (m_to - m_from)*m_progress;
	}
	void Render(){
		AnimationBase::Render();
	}


	double From(){
		return m_from;
	}

	double To(){
		return m_to;
	}

	double Value(){
		return m_value;
	}

protected:
	double m_from;
	double m_to;
	double m_value;
};