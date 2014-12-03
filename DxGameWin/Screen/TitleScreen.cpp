#include "pch.h"
#include "TitleScreen.h"
#include "SoundScreen.h"
#include "GameScreen.h"

using namespace std;
using namespace DX;

TitleScreen::TitleScreen(const shared_ptr<DeviceResources>& deviceResources)
	:ScreenBase(deviceResources){

	texture1 =make_shared<TextureRenderer>(TextureRenderer(m_deviceResources, L"assets\\Logo.png"));
}

void TitleScreen::CreateResources(){
	ScreenBase::CreateResources();

	AddObject(texture1);
}

void TitleScreen::ReleaseResources(){
	ScreenBase::ReleaseResources();
}

ScreenBase* TitleScreen::Update(StepTimer const &timer, const GameInput& input){
	ScreenBase::Update(timer,input);
	
	for (unsigned int i = 0; i < input.m_pointInputs.size(); i++){
		texture1->m_position.x++;
	}

	ScreenBase* nextScreen=this;

	return nextScreen;
}

void TitleScreen::Render(){
	ScreenBase::Render();
}