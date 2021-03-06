#pragma once

#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "ToolkitHelper\GameInput.h"
#include "ToolkitHelper/ScreenBase.h"
#include "Content/SimpleRenderer.h"
#include "Content\SoundObject.h"
#include "ToolkitHelper\GameContext.h"
#include "Animation\PositionAnimation.h"
#include "Content\TextureRenderer.h"

using namespace std;
using namespace DX;
using namespace ToolkitHelper;

class TitleScreen:public ScreenBase{
public:
	TitleScreen(const shared_ptr<GameContext>& gameContext);

	void CreateResources();
	void WindowSizeChanged();
	void ReleaseResources();
	ScreenBase* Update(shared_ptr<FrameContext>& frameContext);
	void Render();
private:
	shared_ptr<TextureRenderer> texture1;

	shared_ptr<PositionAnimation> animation1;
};