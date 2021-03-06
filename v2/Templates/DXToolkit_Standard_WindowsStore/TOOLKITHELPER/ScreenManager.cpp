#include "pch.h"

#include "ScreenManager.h"


using namespace std;
using namespace DX;

namespace ToolkitHelper{

	ScreenManager::ScreenManager(const shared_ptr<GameContext>& gameContext, ScreenBase* currentScreen)
		:m_gameContext(gameContext), m_currentScreen(currentScreen), m_isScreenTranslate(false){

	}

	void ScreenManager::CreateResources(){
		m_currentScreen->CreateResources();
	}

	void ScreenManager::WindowSizeChanged(){

		m_currentScreen->WindowSizeChanged();
	}

	void ScreenManager::ReleaseResources(){
		m_currentScreen->ReleaseResources();
		delete m_currentScreen;
	}

	void ScreenManager::Update(shared_ptr<FrameContext>& frameContext){
		auto nextScreen = m_currentScreen->Update(frameContext);

		if (nextScreen != m_currentScreen){
			m_currentScreen->ReleaseResources();
			delete m_currentScreen;
			m_currentScreen = nextScreen;
			m_currentScreen->CreateResources();
			m_isScreenTranslate = true;
		}
		else{
			m_isScreenTranslate = false;
		}
	}

	void ScreenManager::Render(){
		if (m_isScreenTranslate == false){
			m_currentScreen->Render();
		}
	}

}