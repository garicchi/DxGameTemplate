#pragma once

#include "ToolkitHelper/GameObject.h"

#include "pch.h"
#include "WICTextureLoader.h"
#include "SpriteBatch.h"

using namespace std;
using namespace DX;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace ToolkitHelper;

class TextureRenderer :public GameObject{
public:
	TextureRenderer(const shared_ptr<DeviceResources> &deviceResources,String^ path,D2D1_VECTOR_2F position,D2D1_VECTOR_2F size,float rotation) :
		GameObject(deviceResources),m_path(path),m_position(position),m_size(size),m_rotation(rotation){
		
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
	}

	void Update(DX::StepTimer const& timer, const GameInput& input){
		
	}

	void Render(){
		m_sprite->Begin();

		RECT rect;
		rect.top = m_position.y ;
		rect.left = m_position.x ;
		rect.bottom = m_position.y + m_size.y;
		rect.right = m_position.x + m_size.x;

		m_sprite->Draw(m_texture.Get(), rect, nullptr, Colors::White, m_rotation, XMFLOAT2(m_size.x/2.0, m_size.y/2.0));
		m_sprite->End();
	}

	D2D1_VECTOR_2F m_position;
	D2D1_VECTOR_2F m_size;
	float m_rotation;
protected:
	shared_ptr<SpriteBatch> m_sprite;
	ComPtr<ID3D11ShaderResourceView> m_texture;
	
	String^ m_path;

};