#pragma once
#include "pch.h"
#include "ToolkitHelper\GameObject.h"

namespace ToolkitHelper{

	enum AnimationObjectState{
		Active, Stop
	};

	class AnimationBase :public GameObject{
	public:
		AnimationBase(shared_ptr<GameContext> gameContext)
		:GameObject(gameContext){
			m_animationState = AnimationObjectState::Stop;
			m_beginFlag = false;
		}

		void CreateResources(){

		}
		void WindowSizeChanged(){

		}
		void ReleaseResources(){

		}
		void Update(shared_ptr<FrameContext>& frameContext){
			if (m_animationState != AnimationObjectState::Stop){
				if (m_beginFlag == true){
					m_beginTime = frameContext->m_timer.GetTotalSeconds();
					m_beginFlag = false;
				}

				double currentTime = frameContext->m_timer.GetTotalSeconds() - m_beginTime;
				m_progress = currentTime / m_duration;

				if (m_progress >= 1.0){
					m_progress = 1.0;
					m_animationState = AnimationObjectState::Stop;
				}
			}
		}
		void Render(){

		}

		void Begin(double durationSecond){
			m_progress = 0;
			m_animationState = AnimationObjectState::Active;
			m_beginFlag = true;
			m_duration = durationSecond;
		}

		void End(){
			m_animationState = AnimationObjectState::Stop;
		}
		
		AnimationObjectState GetState(){ return m_animationState; }
		double GetDuration(){ return m_duration; }
		double GetBeginTime(){ return m_beginTime; }
		double GetProgress(){ return m_progress; }
	protected:
		AnimationObjectState m_animationState;
		double m_duration;
		double m_beginTime;
		double m_progress;

		bool m_beginFlag;
	};

}