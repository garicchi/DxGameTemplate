#include "pch.h"
#include "GameScreen.h"

#include "Renderer/TextureRenderer.h"
#include "Renderer\FontRenderer.h"

using namespace std;
using namespace DX;

GameScreen::GameScreen(const shared_ptr<DeviceResources>& deviceResources)
	:ScreenBase(deviceResources){
}

void GameScreen::CreateResources(){
	ScreenBase::CreateResources();

	//AddObject(shared_ptr<TextureRenderer>(new TextureRenderer(m_deviceResources, L"assets\\SmallLogo.png")));
	AddObject(shared_ptr<FontRenderer>(new FontRenderer(m_deviceResources)));
}

void GameScreen::ReleaseResources(){
	ScreenBase::ReleaseResources();
}

ScreenBase* GameScreen::Update(StepTimer const &timer, const GameInput& input){
	ScreenBase::Update(timer,input);

	ScreenBase* nextScreen = this;



	return nextScreen;
}

void GameScreen::Render(){
	ScreenBase::Render();
}