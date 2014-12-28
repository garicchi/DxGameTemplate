#include "pch.h"
#include "TitleScreen.h"
#include "GameScreen.h"
#include "Screen\GameScreen3D.h"

using namespace std;
using namespace DX;
using namespace D2D1;

TitleScreen::TitleScreen(const shared_ptr<GameContext>& gameContext)
	:ScreenBase(gameContext){
	
	//texture1 =make_shared<SimpleRenderer>(SimpleRenderer(m_deviceResources));
}

void TitleScreen::CreateResources(){
	ScreenBase::CreateResources();
	//AddObject(texture1);
}

void TitleScreen::WindowSizeChanged(){
	ScreenBase::WindowSizeChanged();
}

void TitleScreen::ReleaseResources(){
	ScreenBase::ReleaseResources();
}

ScreenBase* TitleScreen::Update(const StepTimer& timer, const GameInput& input){
	ScreenBase::Update(timer,input);
	
	ScreenBase* nextScreen = this;
	for (unsigned int i = 0; i < input.m_pointInputs.size(); i++){
		nextScreen = new GameScreen3D(m_gameContext);
		//texture1->m_rotation += 0.05;
	}

	

	return nextScreen;
}

void TitleScreen::Render(){
	ScreenBase::Render();
}