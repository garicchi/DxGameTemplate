#include "pch.h"
#include "SimpleRenderer.h"

using namespace std;
using namespace DX;

//レンダラーの初期化処理を行う
SimpleRenderer::SimpleRenderer(const shared_ptr<GameContext>& gameContext)
	:GameObject(gameContext){


}

void SimpleRenderer::WindowSizeChanged(){

}

//レンダラーで使うリソースを確保する
void SimpleRenderer::CreateResources(){

}

//レンダラーで使ったリソースを解放する
void SimpleRenderer::ReleaseResources(){

}

//レンダラーの更新処理を行う
void SimpleRenderer::Update(shared_ptr<FrameContext>& frameContext){

}

//レンダラーの描画処理を行う
void SimpleRenderer::Render(){

}