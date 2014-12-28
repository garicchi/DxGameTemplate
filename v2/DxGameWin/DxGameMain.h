#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "ToolkitHelper/ScreenManager.h"
#include "ToolkitHelper\GameContext.h"

using namespace std;
using namespace DX;
using namespace ToolkitHelper;

// Direct2D および 3D コンテンツを画面上でレンダリングします。
namespace DxGame
{
	class DxGameMain : public DX::IDeviceNotify
	{
	public:
		DxGameMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~DxGameMain();
		void CreateWindowSizeDependentResources();
		void Update();
		bool Render();

		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();

		void AddTouch(int id, Windows::Foundation::Point point);
		void UpdateTouch(int id, Windows::Foundation::Point point);
		void RemoveTouch(int id);
#if !(WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
		void KeyDown(Windows::System::VirtualKey key);
		void KeyUp(Windows::System::VirtualKey key);
#endif
	private:
		// デバイス リソースへのキャッシュされたポインター。
		std::shared_ptr<GameContext> m_gameContext;
		std::shared_ptr<DeviceResources> m_deviceResources;

		// TODO: これを独自のコンテンツ レンダラーで置き換えます。
		GameInput m_input;

		// ループ タイマーをレンダリングしています。
		DX::StepTimer m_timer;

		shared_ptr<ScreenManager> m_screenManager;
	};
}