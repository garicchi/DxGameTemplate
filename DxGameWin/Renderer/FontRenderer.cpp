#include "pch.h"
#include "FontRenderer.h"

using namespace std;
using namespace DX;

//�����_���[�̏������������s��
FontRenderer::FontRenderer(const shared_ptr<DeviceResources>& deviceResources)
	:RendererBase(deviceResources){



}

//�����_���[�Ŏg�����\�[�X���m�ۂ���
void FontRenderer::CreateResources(){
	auto device = m_deviceResources->GetD3DDevice();
	auto context = m_deviceResources->GetD3DDeviceContext();

	m_spriteBatch = shared_ptr<SpriteBatch>(new SpriteBatch(context));
	m_spriteFont = shared_ptr<SpriteFont>(new SpriteFont(device,L"assets\\myfile.spritefont"));
}

//�����_���[�Ŏg�������\�[�X���������
void FontRenderer::ReleaseResources(){

}

//�����_���[�̍X�V�������s��
void FontRenderer::Update(StepTimer const &timer, const GameInput& input){

}

//�����_���[�̕`�揈�����s��
void FontRenderer::Render(){
	m_spriteBatch->Begin();
	m_spriteFont->DrawString(m_spriteBatch.get(),L"�ق��ق�",XMFLOAT2(0,0));
	m_spriteBatch->End();
}