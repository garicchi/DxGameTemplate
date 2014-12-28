#include "pch.h"
#include "SpriteFontRenderer.h"

using namespace std;
using namespace DX;

//�����_���[�̏������������s��
SpriteFontRenderer::SpriteFontRenderer(const shared_ptr<GameContext>& gameContext, String^ fontPath, D2D1_VECTOR_2F position, String^ text)
	:GameObject(gameContext),m_path(fontPath),m_position(position){

}

//�����_���[�Ŏg�����\�[�X���m�ۂ���
void SpriteFontRenderer::CreateResources(){
	auto device = m_gameContext->m_deviceResources->GetD3DDevice();
	auto context = m_gameContext->m_deviceResources->GetD3DDeviceContext();

	m_spriteBatch = shared_ptr<SpriteBatch>(new SpriteBatch(context));
	m_spriteFont = shared_ptr<SpriteFont>(new SpriteFont(device,m_path->Data()));
}

void SpriteFontRenderer::WindowSizeChanged(){

}

//�����_���[�Ŏg�������\�[�X���������
void SpriteFontRenderer::ReleaseResources(){
	m_spriteBatch.reset();
    m_spriteFont.reset();
}

//�����_���[�̍X�V�������s��
void SpriteFontRenderer::Update(const StepTimer& timer, const GameInput& input){

}

//�����_���[�̕`�揈�����s��
void SpriteFontRenderer::Render(){
	m_spriteBatch->Begin();
	m_spriteFont->DrawString(m_spriteBatch.get(),m_text->Data(),XMFLOAT2(m_position.x,m_position.y));
	m_spriteBatch->End();
}