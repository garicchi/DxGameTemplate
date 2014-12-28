#include "pch.h"
#include "GameScreen.h"

#include "Content/TextureRenderer.h"
#include "Content\TextRenderer.h"
#include "Content\SoundObject.h"

using namespace std;
using namespace DX;
using namespace D2D1;

GameScreen::GameScreen(const shared_ptr<DeviceResources>& deviceResources)
	:ScreenBase(deviceResources){
}

void GameScreen::CreateResources(){
	ScreenBase::CreateResources();
	
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