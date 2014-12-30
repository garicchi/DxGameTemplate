#include "pch.h"
#include "TitleScreen.h"
#include "GameScreen.h"
#include "Screen\GameScreen3D.h"
#include "ToolkitHelper\SaveDataStore.h"
#include "Common\SaveData.h"

using namespace std;
using namespace DX;
using namespace D2D1;

TitleScreen::TitleScreen(const shared_ptr<GameContext>& gameContext)
	:ScreenBase(gameContext){
	
	texture1 = shared_ptr<TextureRenderer>(new TextureRenderer(m_gameContext,L"assets/star.png",XMFLOAT2(10,10),XMFLOAT2(100,100),0));
	animation1 = shared_ptr<PositionAnimation>(new PositionAnimation(m_gameContext,XMFLOAT2(10,10),XMFLOAT2(500,10)));

	AddObject(texture1);
	AddObject(animation1);
}

void TitleScreen::CreateResources(){
	ScreenBase::CreateResources();
	
	
}

void TitleScreen::WindowSizeChanged(){
	ScreenBase::WindowSizeChanged();
}

void TitleScreen::ReleaseResources(){
	ScreenBase::ReleaseResources();
}

ScreenBase* TitleScreen::Update(shared_ptr<FrameContext>& frameContext){
	ScreenBase::Update(frameContext);
	
	ScreenBase* nextScreen = this;
	for (unsigned int i = 0; i < frameContext->m_input.m_pointInputs.size(); i++){
		//nextScreen = new GameScreen(m_gameContext);
		if (animation1->GetState() == AnimationObjectState::Stop){
			animation1->Begin(2);
		}
		//shared_ptr<SaveDataStore<SaveData>> store=SaveDataStore<SaveData>::getInstance(SaveData::GetType());
		store->GetData()->Num = 6;
		
		store->SaveDataAsync();
	}

	texture1->m_position = animation1->GetValue();

	
	return nextScreen;
}

void TitleScreen::Render(){
	ScreenBase::Render();
	
}