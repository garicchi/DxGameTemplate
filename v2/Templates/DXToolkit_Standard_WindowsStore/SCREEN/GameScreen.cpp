#include "pch.h"
#include "GameScreen.h"

#include "Content/TextureRenderer.h"
#include "Content\TextRenderer.h"

using namespace std;
using namespace DX;
using namespace D2D1;

GameScreen::GameScreen(const shared_ptr<GameContext>& gameContext)
	:ScreenBase(gameContext){
}

void GameScreen::CreateResources(){
	ScreenBase::CreateResources();

	AddObject(shared_ptr<TextRenderer>(new TextRenderer(m_gameContext, "もんじゃ焼き", "Segoe UI", Point2F(10, 10), ColorF::White, 34.0f)));
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