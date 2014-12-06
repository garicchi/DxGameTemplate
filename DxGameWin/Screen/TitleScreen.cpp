#include "pch.h"
#include "TitleScreen.h"
#include "GameScreen.h"

using namespace std;
using namespace DX;
using namespace D2D1;

TitleScreen::TitleScreen(const shared_ptr<DeviceResources>& deviceResources)
	:ScreenBase(deviceResources){
	
	texture1 =make_shared<TextureRenderer>(TextureRenderer(m_deviceResources, "assets/star2.png",Vector2F(500,300),Vector2F(100,100),0.0f));
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
		
		texture1->m_rotation += 0.05;
	}

	ScreenBase* nextScreen=this;

	return nextScreen;
}

void TitleScreen::Render(){
	ScreenBase::Render();
}