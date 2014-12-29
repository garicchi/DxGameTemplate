#pragma once;
#include "pch.h"
#include "ToolkitHelper\AnimationBase.h"

using namespace ToolkitHelper;

class PositionAnimation :public AnimationBase{
public:
	PositionAnimation(const shared_ptr<GameContext>& gameContext, D2D1_VECTOR_2F from, D2D1_VECTOR_2F to)
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

		m_value.x = m_from.x + (m_to.x - m_from.x)*m_progress;
		m_value.y = m_from.y + (m_to.y - m_from.y)*m_progress;
	}
	void Render(){
		AnimationBase::Render();
	}


	D2D1_VECTOR_2F GetFrom(){
		return m_from;
	}

	D2D1_VECTOR_2F GetTo(){
		return m_to;
	}

	D2D1_VECTOR_2F GetValue(){
		return m_value;
	}

protected:

	D2D1_VECTOR_2F m_from;
	D2D1_VECTOR_2F m_to;
	D2D1_VECTOR_2F m_value;
};