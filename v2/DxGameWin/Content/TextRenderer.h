#pragma once

#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "ToolkitHelper\GameInput.h"
#include "ToolkitHelper/GameObject.h"
#include "ToolkitHelper\GameContext.h"

using namespace std;
using namespace DX;
using namespace ToolkitHelper;
using namespace Platform;
using namespace DirectX;
using namespace D2D1;
using namespace Microsoft::WRL;

class TextRenderer :public GameObject{
public:
	TextRenderer(const shared_ptr<GameContext>& gameContext, String^ text, String^ font, XMFLOAT2 position, ColorF color, float fontSize);

	void CreateResources();
	void WindowSizeChanged();
	void ReleaseResources();
	void Update(shared_ptr<FrameContext>& frameContext);
	void Render();

	String^ m_text;
	XMFLOAT2 m_position;
	ColorF m_color;
	float m_fontSize;
protected:
	String^ m_font;

	ComPtr<ID2D1SolidColorBrush> m_textBrush;
	ComPtr<IDWriteTextLayout> m_textLayout;
	ComPtr<IDWriteTextFormat> m_textFormat;

};