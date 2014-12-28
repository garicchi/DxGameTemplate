#pragma once

#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "ToolkitHelper\GameInput.h"
#include "ToolkitHelper/GameObject.h"

#include"SpriteFont.h"
using namespace std;
using namespace DX;
using namespace ToolkitHelper;
using namespace DirectX;
using namespace Platform;

class SpriteFontRenderer :public GameObject{
public:
	SpriteFontRenderer(const shared_ptr<GameContext>& gameContext, String^ fontPath, D2D1_VECTOR_2F position, String^ text);

	void CreateResources();
	void WindowSizeChanged();
	void ReleaseResources();
	void Update(const StepTimer& timer,const GameInput& input);
	void Render();


	D2D1_VECTOR_2F m_position;
	String^ m_text;
protected:
	shared_ptr<SpriteFont> m_spriteFont;
	shared_ptr<SpriteBatch> m_spriteBatch;
	String^ m_path;

};