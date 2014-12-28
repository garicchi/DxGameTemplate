#pragma once

#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "ToolkitHelper/ScreenBase.h"
#include "ToolkitHelper\GameInput.h"

#include "ToolkitHelper\Graphics.h"
#include "ToolkitHelper\Constants.h"
#include "ToolkitHelper\SkinnedMeshRenderer.h"
#include "ToolkitHelper\SkinMeshModel.h"
#include "ToolkitHelper\GameContext.h"

using namespace std;
using namespace DX;
using namespace ToolkitHelper;

class GameScreen3D :public ScreenBase{
public:
	GameScreen3D(const shared_ptr<GameContext>& gameContext);

	void CreateResources();
	void WindowSizeChanged();
	void ReleaseResources();
	ScreenBase* Update(const StepTimer& timer, const GameInput& input);
	void Render();

protected:
	Graphics m_graphics;
	LightConstants m_lightConstants;
	MiscConstants m_miscConstants;

	bool m_loadingComplete;

	shared_ptr<SkinnedMeshRenderer> m_skinnedMeshRenderer;

	shared_ptr<SkinMeshModel> m_model;
};