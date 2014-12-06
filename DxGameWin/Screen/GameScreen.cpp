#include "pch.h"
#include "GameScreen.h"

#include "Content/TextureRenderer.h"
#include "Content\TextRenderer.h"

using namespace std;
using namespace DX;
using namespace D2D1;

GameScreen::GameScreen(const shared_ptr<DeviceResources>& deviceResources)
	:ScreenBase(deviceResources){
}

void GameScreen::CreateResources(){
	ScreenBase::CreateResources();

	AddObject(shared_ptr<TextRenderer>(new TextRenderer(m_deviceResources,"Ç‡ÇÒÇ∂Ç·èƒÇ´","Segoe UI",Point2F(10,10),ColorF::White,34.0f)));
}

void GameScreen::ReleaseResources(){
	ScreenBase::ReleaseResources();
}

ScreenBase* GameScreen::Update(const StepTimer& timer, const GameInput& input){
	ScreenBase::Update(timer,input);

	ScreenBase* nextScreen = this;



	return nextScreen;
}

void GameScreen::Render(){
	ScreenBase::Render();
}