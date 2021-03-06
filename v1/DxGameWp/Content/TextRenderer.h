#pragma once

#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "ToolkitHelper\GameInput.h"
#include "ToolkitHelper/GameObject.h"


using namespace std;
using namespace DX;
using namespace ToolkitHelper;
using namespace Platform;
using namespace DirectX;
using namespace D2D1;
using namespace Microsoft::WRL;

class TextRenderer :public GameObject{
public:
	TextRenderer(const shared_ptr<DeviceResources>& deviceResources, String^ text, String^ font, D2D1_POINT_2F position, ColorF color, float fontSize);

	void CreateResources();
	void ReleaseResources();
	void Update(const StepTimer& timer, const GameInput& input);
	void Render();

	String^ m_text;
	D2D1_POINT_2F m_position;
	ColorF m_color;
	float m_fontSize;
protected:
	String^ m_font;

	ComPtr<ID2D1SolidColorBrush> m_textBrush;
	ComPtr<IDWriteTextLayout> m_textLayout;
	ComPtr<IDWriteTextFormat> m_textFormat;

};