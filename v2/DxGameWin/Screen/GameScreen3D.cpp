#include "pch.h"
#include "GameScreen3D.h"

#include "Content/TextureRenderer.h"
#include "Content\TextRenderer.h"

using namespace std;
using namespace DX;
using namespace D2D1;
using namespace DirectX;

GameScreen3D::GameScreen3D(const shared_ptr<DeviceResources>& deviceResources)
	:ScreenBase(deviceResources){

	m_loadingComplete = false;
}

void GameScreen3D::CreateResources(){
	ScreenBase::CreateResources();

	m_graphics.Initialize(m_deviceResources->GetD3DDevice(), m_deviceResources->GetD3DDeviceContext(), m_deviceResources->GetDeviceFeatureLevel());

	// Set DirectX to not cull any triangles so the entire mesh will always be shown.
	CD3D11_RASTERIZER_DESC d3dRas(D3D11_DEFAULT);
	d3dRas.CullMode = D3D11_CULL_NONE;
	d3dRas.MultisampleEnable = true;
	d3dRas.AntialiasedLineEnable = true;

	ComPtr<ID3D11RasterizerState> p3d3RasState;
	m_deviceResources->GetD3DDevice()->CreateRasterizerState(&d3dRas, &p3d3RasState);
	m_deviceResources->GetD3DDeviceContext()->RSSetState(p3d3RasState.Get());

	m_model = shared_ptr<SkinMeshModel>(new SkinMeshModel(make_shared<Graphics>(m_graphics), L"teapot.cmo", L"", L""));
	auto loadMeshTask = m_model->LoadMeshAsync();

	m_skinnedMeshRenderer = shared_ptr<SkinnedMeshRenderer>(new SkinnedMeshRenderer());
	auto initializeSkinnedMeshRendererTask = m_skinnedMeshRenderer->InitializeAsync(m_deviceResources->GetD3DDevice(), m_deviceResources->GetD3DDeviceContext(),L"SkinningVertexShader.cso");

	(loadMeshTask && initializeSkinnedMeshRendererTask).then([this]()
	{
		// Scene is ready to be rendered.
		m_loadingComplete = true;
	});

	/*---WindowSize Dependent---*/
	m_miscConstants.ViewportHeight = m_deviceResources->GetScreenViewport().Height;
	m_miscConstants.ViewportWidth = m_deviceResources->GetScreenViewport().Width;
	m_graphics.UpdateMiscConstants(m_miscConstants);

	m_graphics.GetCamera().SetOrientationMatrix(m_deviceResources->GetOrientationTransform3D());

	Windows::Foundation::Size outputSize = m_deviceResources->GetOutputSize();

	// Setup the camera parameters for our scene.
	m_graphics.GetCamera().SetViewport((UINT) outputSize.Width, (UINT) outputSize.Height);
	m_graphics.GetCamera().SetPosition(XMFLOAT3(0.0f, 6.0f, -18.0f));
	m_graphics.GetCamera().SetLookAt(XMFLOAT3(0.0f, 0.0f, 0.0f));

	float aspectRatio = outputSize.Width / outputSize.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	if (aspectRatio < 1.0f)
	{
		// Portrait or snap view
		m_graphics.GetCamera().SetUpVector(XMFLOAT3(1.0f, 0.0f, 0.0f));
		fovAngleY = 120.0f * XM_PI / 180.0f;
	}
	else
	{
		// Landscape view.
		m_graphics.GetCamera().SetUpVector(XMFLOAT3(0.0f, 1.0f, 0.0f));
	}

	m_graphics.GetCamera().SetProjection(fovAngleY, aspectRatio, 1.0f, 1000.0f);

	// Setup lighting for our scene.
	static const XMVECTORF32 s_vPos = { 5.0f, 5.0f, -2.5f, 0.f };

	XMFLOAT4 dir;
	DirectX::XMStoreFloat4(&dir, XMVector3Normalize(s_vPos));

	m_lightConstants.ActiveLights = 1;
	m_lightConstants.Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_lightConstants.IsPointLight[0] = false;
	m_lightConstants.LightColor[0] = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_lightConstants.LightDirection[0] = dir;
	m_lightConstants.LightSpecularIntensity[0].x = 2;

	m_graphics.UpdateLightConstants(m_lightConstants);
}

void GameScreen3D::ReleaseResources(){
	ScreenBase::ReleaseResources();

	m_model.reset();
	m_loadingComplete = false;
}

ScreenBase* GameScreen3D::Update(const StepTimer& timer, const GameInput& input){
	ScreenBase::Update(timer, input);

	ScreenBase* nextScreen = this;

	auto timeDelta = static_cast<float>(timer.GetElapsedSeconds());


	// Update animated models.
	m_skinnedMeshRenderer->UpdateAnimation(timeDelta, m_model->MeshModels());

	// Rotate scene.
	//m_rotation = static_cast<float>(timer.GetTotalSeconds()) * 0.5f;

	// Update the "time" variable for the glow effect.
	for (float &time : m_model->Times())
	{
		time = std::max<float>(0.0f, time - timeDelta);
	}

	return nextScreen;
}

void GameScreen3D::Render(){
	ScreenBase::Render();
	
	if (!m_loadingComplete)
	{
		return;
	}

	auto context = m_deviceResources->GetD3DDeviceContext();

	// Set render targets to the screen.
	auto rtv = m_deviceResources->GetBackBufferRenderTargetView();
	auto dsv = m_deviceResources->GetDepthStencilView();
	ID3D11RenderTargetView *const targets[1] = { rtv };
	context->OMSetRenderTargets(1, targets, dsv);

	XMMATRIX rotation = XMMatrixRotationY(/*m_rotation*/0);
	for (UINT i = 0; i < m_model->MeshModels().size(); i++)
	{
		XMMATRIX modelTransform = rotation;

		modelTransform = XMLoadFloat4x4(&m_model->Transform()) * modelTransform;

		// Update the time shader variable for the objects in our scene.
		m_miscConstants.Time = m_model->Times()[i];
		m_graphics.UpdateMiscConstants(m_miscConstants);

		// Draw the models.
		if (m_model->MeshModels()[i]->Tag != nullptr)
		{

			// Mesh has animation - render skinned mesh.
			m_skinnedMeshRenderer->RenderSkinnedMesh(m_model->MeshModels()[i], m_graphics, modelTransform);
		}
		else
		{
			// Mesh does not have animation - render as usual.
			m_model->MeshModels()[i]->Render(m_graphics, modelTransform);
		}
	}
}