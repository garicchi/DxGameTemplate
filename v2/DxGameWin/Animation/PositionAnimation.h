#pragma once;
#include "pch.h"
#include "ToolkitHelper\AnimationBase.h"

using namespace ToolkitHelper;

class PositionAnimation :public AnimationBase{
public:
	PositionAnimation(const shared_ptr<GameContext>& gameContext, XMFLOAT2 from, XMFLOAT2 to)
		:AnimationBase(gameContext), m_from(from), m_to(to), m_value(from){

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

		m_value.x = static_cast<float>(m_from.x + (m_to.x - m_from.x)*m_progress);
		m_value.y = static_cast<float>(m_from.y + (m_to.y - m_from.y)*m_progress);
	}
	void Render(){
		AnimationBase::Render();
	}


	XMFLOAT2 GetFrom(){
		return m_from;
	}

	XMFLOAT2 GetTo(){
		return m_to;
	}

	XMFLOAT2 GetValue(){
		return m_value;
	}

protected:

	XMFLOAT2 m_from;
	XMFLOAT2 m_to;
	XMFLOAT2 m_value;
};