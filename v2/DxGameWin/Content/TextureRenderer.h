#pragma once

#include "ToolkitHelper/GameObject.h"

#include "pch.h"
#include "WICTextureLoader.h"
#include "SpriteBatch.h"
#include "ToolkitHelper\GameContext.h"

using namespace std;
using namespace DX;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace ToolkitHelper;

class TextureRenderer :public GameObject{
public:
	TextureRenderer(const shared_ptr<GameContext> &gameContext,String^ path,XMFLOAT2 position,XMFLOAT2 size,float rotation) :
		GameObject(gameContext),m_path(path),m_position(position),m_size(size),m_rotation(rotation){
		
	}

	void CreateResources(){
		auto device = m_gameContext->m_deviceResources->GetD3DDevice();
		auto context = m_gameContext->m_deviceResources->GetD3DDeviceContext();

		m_sprite.reset(new SpriteBatch(context));
		
		CreateWICTextureFromFile(device, m_path->Data(), nullptr, m_texture.ReleaseAndGetAddressOf());

	}

	void WindowSizeChanged(){

	}

	void ReleaseResources(){
		m_sprite.reset();
		
		m_texture.Reset();
	}

	void Update(shared_ptr<FrameContext>& frameContext){
		
	}

	void Render(){
		m_sprite->Begin();

		RECT rect;
		rect.top = static_cast<int>(m_position.y);
		rect.left = static_cast<int>(m_position.x);
		rect.bottom = static_cast<int>(m_position.y + m_size.y);
		rect.right = static_cast<int>(m_position.x + m_size.x);

		m_sprite->Draw(m_texture.Get(), rect, nullptr, Colors::White, m_rotation, XMFLOAT2(0,0));
		m_sprite->End();
	}

	XMFLOAT2 m_position;
	XMFLOAT2 m_size;
	float m_rotation;
protected:
	shared_ptr<SpriteBatch> m_sprite;
	ComPtr<ID3D11ShaderResourceView> m_texture;
	
	String^ m_path;

};