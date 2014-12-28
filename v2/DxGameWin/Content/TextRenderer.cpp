#include "pch.h"
#include "TextRenderer.h"

using namespace std;
using namespace DX;

//�����_���[�̏������������s��
TextRenderer::TextRenderer(const shared_ptr<DeviceResources>& deviceResources, String^ text, String^ font, D2D1_POINT_2F position, ColorF color, float fontSize)
	:GameObject(deviceResources),m_text(text),m_font(font),m_position(position),m_color(color),m_fontSize(fontSize){

	
}

//�����_���[�Ŏg�����\�[�X���m�ۂ���
void TextRenderer::CreateResources(){
	//�e�L�X�g�g�p����u���V���m�ۂ��܂�
	m_deviceResources->GetD2DDeviceContext()->CreateSolidColorBrush(m_color, &m_textBrush);

	//�e�L�X�g�Ɏg�p����t�H�[�}�b�g���m�ۂ��܂�
	m_deviceResources->GetDWriteFactory()->CreateTextFormat(
		m_font->Data(),
		nullptr,
		DWRITE_FONT_WEIGHT_LIGHT,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		m_fontSize,
		L"ja-JP",
		&m_textFormat
		);

}

void TextRenderer::WindowSizeChanged(){

}

//�����_���[�Ŏg�������\�[�X���������
void TextRenderer::ReleaseResources(){
	m_textBrush.Reset();
	m_textFormat.Reset();
	m_textLayout.Reset();
}

//�����_���[�̍X�V�������s��
void TextRenderer::Update(const StepTimer& timer, const GameInput& input){
	m_deviceResources->GetDWriteFactory()->CreateTextLayout(
		m_text->Data(),
		(uint32) m_text->Length(),
		m_textFormat.Get(),
		240.0f, // ���̓e�L�X�g�̍ő啝�B
		50.0f, // ���̓e�L�X�g�̍ő卂���B
		&m_textLayout
		);
}

//�����_���[�̕`�揈�����s��
void TextRenderer::Render(){
	//�f�o�C�X�R���e�L�X�g�̊m��
	ID2D1DeviceContext* context = m_deviceResources->GetD2DDeviceContext();

	context->BeginDraw(); //�`��J�n

	context->DrawTextLayout(m_position,
		m_textLayout.Get(), m_textBrush.Get());

	context->EndDraw();	//�`��I��
}