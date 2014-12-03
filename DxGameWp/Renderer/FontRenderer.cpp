#include "pch.h"
#include "FontRenderer.h"

using namespace std;
using namespace DX;

//レンダラーの初期化処理を行う
FontRenderer::FontRenderer(const shared_ptr<DeviceResources>& deviceResources)
	:RendererBase(deviceResources){



}

//レンダラーで使うリソースを確保する
void FontRenderer::CreateResources(){
	auto device = m_deviceResources->GetD3DDevice();
	auto context = m_deviceResources->GetD3DDeviceContext();

	m_spriteBatch = shared_ptr<SpriteBatch>(new SpriteBatch(context));
	m_spriteFont = shared_ptr<SpriteFont>(new SpriteFont(device,L"assets\\myfile.spritefont"));
}

//レンダラーで使ったリソースを解放する
void FontRenderer::ReleaseResources(){

}

//レンダラーの更新処理を行う
void FontRenderer::Update(StepTimer const &timer, const GameInput& input){

}

//レンダラーの描画処理を行う
void FontRenderer::Render(){
	m_spriteBatch->Begin();
	m_spriteFont->DrawString(m_spriteBatch.get(),L"ほげほげ",XMFLOAT2(0,0));
	m_spriteBatch->End();
}