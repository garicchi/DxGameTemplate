#include "pch.h"
#include "SimpleRenderer.h"

using namespace std;
using namespace DX;

//レンダラーの初期化処理を行う
SimpleRenderer::SimpleRenderer(const shared_ptr<DeviceResources>& deviceResources)
	:GameObject(deviceResources){


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
void SimpleRenderer::Update(const StepTimer& timer, const GameInput& input){

}

//レンダラーの描画処理を行う
void SimpleRenderer::Render(){

}