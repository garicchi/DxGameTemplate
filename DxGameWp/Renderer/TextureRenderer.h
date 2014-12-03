#pragma once

#include "DXTKHelper/RendererBase.h"

#include "pch.h"
#include "WICTextureLoader.h"
#include "SpriteBatch.h"

using namespace std;
using namespace DX;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace DXTKHelper;

class TextureRenderer :public RendererBase{
public:
	TextureRenderer(const shared_ptr<DeviceResources> &deviceResources,String^ path) :
		RendererBase(deviceResources){
		m_path = path;
		m_position = XMFLOAT2(10,10);
	}

	void CreateResources(){
		auto device = m_deviceResources->GetD3DDevice();
		auto context = m_deviceResources->GetD3DDeviceContext();

		m_sprite.reset(new SpriteBatch(context));

		CreateWICTextureFromFile(device, m_path->Data(), nullptr, m_texture.ReleaseAndGetAddressOf());

	}

	void ReleaseResources(){
		m_sprite.reset();
		m_texture.Reset();
		delete m_path;
	}

	void Update(DX::StepTimer const& timer, const GameInput& input){

	}

	void Render(){
		m_sprite->Begin();

		m_sprite->Draw(m_texture.Get(), m_position, nullptr, Colors::White);

		m_sprite->End();
	}

	XMFLOAT2 m_position;

protected:
	shared_ptr<SpriteBatch> m_sprite;
	ComPtr<ID3D11ShaderResourceView> m_texture;
	
	String^ m_path;

};