#include "pch.h"
#include "SpriteFontRenderer.h"

using namespace std;
using namespace DX;

//レンダラーの初期化処理を行う
SpriteFontRenderer::SpriteFontRenderer(const shared_ptr<DeviceResources>& deviceResources,String^ fontPath,XMFLOAT2 position,String^ text)
	:GameObject(deviceResources),m_path(fontPath),m_position(position){

}

//レンダラーで使うリソースを確保する
void SpriteFontRenderer::CreateResources(){
	auto device = m_deviceResources->GetD3DDevice();
	auto context = m_deviceResources->GetD3DDeviceContext();

	m_spriteBatch = shared_ptr<SpriteBatch>(new SpriteBatch(context));
	m_spriteFont = shared_ptr<SpriteFont>(new SpriteFont(device,m_path->Data()));
}

//レンダラーで使ったリソースを解放する
void SpriteFontRenderer::ReleaseResources(){
	m_spriteBatch.reset();
    m_spriteFont.reset();
}

//レンダラーの更新処理を行う
void SpriteFontRenderer::Update(StepTimer const &timer, const GameInput& input){

}

//レンダラーの描画処理を行う
void SpriteFontRenderer::Render(){
	m_spriteBatch->Begin();
	m_spriteFont->DrawString(m_spriteBatch.get(),m_text->Data(),m_position);
	m_spriteBatch->End();
}