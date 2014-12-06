#include "pch.h"
#include "DxGameMain.h"
#include "Common/DirectXHelper.h"
#include "ToolkitHelper/ScreenBase.h"
#include "Screen/TitleScreen.h"
#include "ToolkitHelper\GameInput.h"
#include "Screen\GameScreen.h"

using namespace DxGame;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;
using namespace ToolkitHelper;

// アプリケーションの読み込み時にアプリケーション資産を読み込んで初期化します。
DxGameMain::DxGameMain(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
m_deviceResources(deviceResources)
{
	// デバイスが失われたときや再作成されたときに通知を受けるように登録します
	m_deviceResources->RegisterDeviceNotify(this);

	//ゲーム画面を横に固定する場合
	m_deviceResources->SetCurrentOrientation(Windows::Graphics::Display::DisplayOrientations::Landscape);


	// TODO: これをアプリのコンテンツの初期化で置き換えます。

	// TODO: 既定の可変タイムステップ モード以外のモードが必要な場合は、タイマー設定を変更してください。
	// 例: 60 FPS 固定タイムステップ更新ロジックでは、次を呼び出します:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/
	m_screenManager = shared_ptr<ScreenManager>(new ScreenManager(m_deviceResources, new TitleScreen(deviceResources)));
	m_screenManager->CreateResources();
}

DxGameMain::~DxGameMain()
{
	// デバイスの通知を登録解除しています
	m_deviceResources->RegisterDeviceNotify(nullptr);
}

// ウィンドウのサイズが変更される (デバイスの方向が変更されるなど) 場合に、 アプリケーションの状態を更新します。
void DxGameMain::CreateWindowSizeDependentResources()
{
	// TODO: これをアプリのコンテンツのサイズに依存する初期化で置き換えます。
	m_screenManager->CreateResources();
}

// アプリケーション状態をフレームごとに 1 回更新します。
void DxGameMain::Update()
{
	// シーン オブジェクトを更新します。
	m_timer.Tick([&]()
	{
		// TODO: これをアプリのコンテンツの更新関数で置き換えます。
#pragma region XINPUT
		//XInputを使うにはリンカーの入力にxinput.lib;を追加する
		/*
		#if WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP
		XINPUT_STATE inputState;
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++){
		DWORD result = XInputGetState(i, &inputState);

		if (result == ERROR_SUCCESS){
		SHORT thumbLeftX = inputState.Gamepad.sThumbLX;
		SHORT thumbLeftY = inputState.Gamepad.sThumbLY;
		SHORT thumbRightX = inputState.Gamepad.sThumbRX;
		SHORT thumbRightY = inputState.Gamepad.sThumbRY;
		BYTE leftTrigger = inputState.Gamepad.bLeftTrigger;
		BYTE rightTrigger = inputState.Gamepad.bRightTrigger;
		WORD btn = inputState.Gamepad.wButtons;
		}


		}
		#endif
		*/
#pragma endregion

		//レンダラーの更新処理をする
		m_screenManager->Update(m_timer, m_input);
	});
}

// 現在のアプリケーション状態に応じて現在のフレームをレンダリングします。
// フレームがレンダリングされ、表示準備が完了すると、true を返します。
bool DxGameMain::Render()
{
	// 初回更新前にレンダリングは行わないようにしてください。
	if (m_timer.GetFrameCount() == 0)
	{
		return false;
	}

	auto context = m_deviceResources->GetD3DDeviceContext();

	// ビューポートをリセットして全画面をターゲットとします。
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	// レンダリング ターゲットを画面にリセットします。
	ID3D11RenderTargetView *const targets[1] = { m_deviceResources->GetBackBufferRenderTargetView() };
	context->OMSetRenderTargets(1, targets, m_deviceResources->GetDepthStencilView());

	// バック バッファーと深度ステンシル ビューをクリアします。
	context->ClearRenderTargetView(m_deviceResources->GetBackBufferRenderTargetView(), DirectX::Colors::CornflowerBlue);
	context->ClearDepthStencilView(m_deviceResources->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// シーン オブジェクトをレンダリングします。
	// TODO: これをアプリのコンテンツのレンダリング関数で置き換えます。

	//レンダラーの描画処理を行う
	m_screenManager->Render();
	return true;
}

// デバイス リソースを解放する必要が生じたことをレンダラーに通知します。
void DxGameMain::OnDeviceLost()
{
	//レンダラーのリソースをリリースする
	m_screenManager->ReleaseResources();
}

// デバイス リソースの再作成が可能になったことをレンダラーに通知します。
void DxGameMain::OnDeviceRestored()
{
	//レンダラーのリソースを初期化する
	m_screenManager->CreateResources();
	CreateWindowSizeDependentResources();
}


void DxGameMain::AddTouch(int id, Windows::Foundation::Point point)
{
	m_input.AddTouch(id, point);
}

void DxGameMain::UpdateTouch(int id, Windows::Foundation::Point point)
{
	m_input.UpdateTouch(id, point);
}

void DxGameMain::RemoveTouch(int id)
{
	m_input.RemoveTouch(id);
}
#if !(WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
void DxGameMain::KeyDown(Windows::System::VirtualKey key)
{
	m_input.AddKey(key);
}

void DxGameMain::KeyUp(Windows::System::VirtualKey key)
{
	m_input.RemoveKey(key);
}

#endif