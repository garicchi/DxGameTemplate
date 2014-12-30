#include "pch.h"
#include "GameScreen.h"

#include "Content/TextureRenderer.h"


using namespace std;
using namespace DX;
using namespace D2D1;

GameScreen::GameScreen(const shared_ptr<GameContext>& gameContext)
	:ScreenBase(gameContext){
	text1 = shared_ptr<TextRenderer>(new TextRenderer(m_gameContext, "Ç‡ÇÒÇ∂Ç·èƒÇ´", "Segoe UI", XMFLOAT2(10, 10), ColorF::White, 34.0f));
	AddObject(text1);
}

void GameScreen::CreateResources(){
	ScreenBase::CreateResources();

	
}

void GameScreen::WindowSizeChanged(){
	ScreenBase::WindowSizeChanged();
}

void GameScreen::ReleaseResources(){
	ScreenBase::ReleaseResources();
}

ScreenBase* GameScreen::Update(shared_ptr<FrameContext>& frameContext){
	ScreenBase::Update(frameContext);

	ScreenBase* nextScreen = this;



	return nextScreen;
}

void GameScreen::Render(){
	ScreenBase::Render();
}