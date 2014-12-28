#include "pch.h"
#include "TextRenderer.h"

using namespace std;
using namespace DX;

//レンダラーの初期化処理を行う
TextRenderer::TextRenderer(const shared_ptr<DeviceResources>& deviceResources, String^ text, String^ font, D2D1_POINT_2F position, ColorF color, float fontSize)
	:GameObject(deviceResources),m_text(text),m_font(font),m_position(position),m_color(color),m_fontSize(fontSize){

	
}

//レンダラーで使うリソースを確保する
void TextRenderer::CreateResources(){
	//テキスト使用するブラシを確保します
	m_deviceResources->GetD2DDeviceContext()->CreateSolidColorBrush(m_color, &m_textBrush);

	//テキストに使用するフォーマットを確保します
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

//レンダラーで使ったリソースを解放する
void TextRenderer::ReleaseResources(){
	m_textBrush.Reset();
	m_textFormat.Reset();
	m_textLayout.Reset();
}

//レンダラーの更新処理を行う
void TextRenderer::Update(const StepTimer& timer, const GameInput& input){
	m_deviceResources->GetDWriteFactory()->CreateTextLayout(
		m_text->Data(),
		(uint32) m_text->Length(),
		m_textFormat.Get(),
		240.0f, // 入力テキストの最大幅。
		50.0f, // 入力テキストの最大高さ。
		&m_textLayout
		);
}

//レンダラーの描画処理を行う
void TextRenderer::Render(){
	//デバイスコンテキストの確保
	ID2D1DeviceContext* context = m_deviceResources->GetD2DDeviceContext();

	context->BeginDraw(); //描画開始

	context->DrawTextLayout(m_position,
		m_textLayout.Get(), m_textBrush.Get());

	context->EndDraw();	//描画終了
}