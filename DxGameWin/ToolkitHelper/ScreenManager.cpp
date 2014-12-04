#include "pch.h"

#include "ScreenManager.h"


using namespace std;
using namespace DX;
using namespace ToolkitHelper;

ScreenManager::ScreenManager(const shared_ptr<DeviceResources>& deviceResources,ScreenBase* currentScreen)
	:m_deviceResources(deviceResources),m_currentScreen(currentScreen){
	
}

void ScreenManager::CreateResources(){
	m_currentScreen->CreateResources();
}

void ScreenManager::ReleaseResources(){
	m_currentScreen->ReleaseResources();
	delete m_currentScreen;
}

void ScreenManager::Update(StepTimer const& timer,const GameInput& input){
	auto nextScreen = m_currentScreen->Update(timer,input);
	
	if (nextScreen != m_currentScreen){
		m_currentScreen->ReleaseResources();
		delete m_currentScreen;
		m_currentScreen=nextScreen;
		m_currentScreen->CreateResources();
		
	}
}

void ScreenManager::Render(){
	m_currentScreen->Render();
}
