#pragma once
#include "pch.h"

#include "Mesh.h"
#include "Graphics.h"
#include "SkinnedMeshRenderer.h"
#include <ppltasks.h>
#include "DirectXHelpers.h"

using namespace std;
using namespace concurrency;
using namespace DirectX;

namespace{

}//anonymous

class SkinMeshModel{
public:
	SkinMeshModel(shared_ptr<Graphics> graphics,
		const std::wstring& meshFilename,
		const std::wstring& shaderPathLocation,
		const std::wstring& texturePathLocation
		) :m_graphics(graphics), m_meshFilename(meshFilename), m_shaderPathLocation(shaderPathLocation), m_texturePathLocation(texturePathLocation){

	}

	~SkinMeshModel(){
		for (Mesh* m : m_meshModels)
		{
			if (m != nullptr)
			{
				AnimationState* animState = (AnimationState*) m->Tag;
				if (animState != nullptr)
				{
					m->Tag = nullptr;
					delete animState;
				}
			}
			delete m;
		}
		m_meshModels.clear();
	}

	task<void> LoadMeshAsync(){
		// Load the scene objects.
		auto loadMeshTask = Mesh::LoadFromFileAsync(
			*m_graphics.get(),
			m_meshFilename,
			m_shaderPathLocation,
			m_texturePathLocation,
			m_meshModels).then([this]()
		{


			// Initialize animated models.
			for (Mesh* m : m_meshModels)
			{
				if (m->BoneInfoCollection().empty() == false)
				{
					auto animState = new AnimationState();
					animState->m_boneWorldTransforms.resize(m->BoneInfoCollection().size());

					m->Tag = animState;
				}
			}
			// Create a scaling transformation for the teapot model.
			XMStoreFloat4x4(&m_transform, XMMatrixScaling(0.044f, 0.044f, 0.044f) * XMMatrixTranslation(0.0f, -1.6f, 0.0f));

			// Each mesh object has its own "time" used to control the glow effect.
			m_time.clear();
			for (size_t i = 0; i < m_meshModels.size(); i++)
			{
				m_time.push_back(0.0f);
			}
		});
		return loadMeshTask;


	}

	vector<Mesh*>& MeshModels(){ return m_meshModels; }
	XMFLOAT4X4& Transform(){ return m_transform; }
	vector<float>& Times(){ return m_time; }

protected:
	wstring m_meshFilename;
	wstring m_shaderPathLocation;
	wstring m_texturePathLocation;
	vector<Mesh*> m_meshModels;
	shared_ptr<Graphics> m_graphics;

	vector<float> m_time;

	XMFLOAT4X4 m_transform;
};