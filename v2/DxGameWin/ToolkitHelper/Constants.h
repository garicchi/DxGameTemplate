#pragma once
#include "pch.h"

///////////////////////////////////////////////////////////////////////////////////////////
//
// Constant buffer structures
//
// These structs use padding and different data types in places to adhere
// to the shader constant's alignment.
//

namespace ToolkitHelper{

	struct MaterialConstants
	{
		MaterialConstants()
		{
			static_assert((sizeof(MaterialConstants) % 16) == 0, "CB must be 16-byte aligned");
			Ambient = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
			Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			Specular = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
			Emissive = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
			SpecularPower = 1.0f;
			Padding0 = 0.0f;
			Padding1 = 0.0f;
			Padding2 = 0.0f;
		}

		DirectX::XMFLOAT4   Ambient;
		DirectX::XMFLOAT4   Diffuse;
		DirectX::XMFLOAT4   Specular;
		DirectX::XMFLOAT4   Emissive;
		float               SpecularPower;
		float               Padding0;
		float               Padding1;
		float               Padding2;
	};

	struct LightConstants
	{
		LightConstants()
		{
			static_assert((sizeof(LightConstants) % 16) == 0, "CB must be 16-byte aligned");
			ZeroMemory(this, sizeof(LightConstants));
			Ambient = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		}

		DirectX::XMFLOAT4   Ambient;
		DirectX::XMFLOAT4   LightColor[4];
		DirectX::XMFLOAT4   LightAttenuation[4];
		DirectX::XMFLOAT4   LightDirection[4];
		DirectX::XMFLOAT4   LightSpecularIntensity[4];
		UINT                IsPointLight[4];
		UINT                ActiveLights;
		float               Padding0;
		float               Padding1;
		float               Padding2;
	};

	struct ObjectConstants
	{
		ObjectConstants()
		{
			static_assert((sizeof(ObjectConstants) % 16) == 0, "CB must be 16-byte aligned");
			ZeroMemory(this, sizeof(ObjectConstants));
		}

		DirectX::XMMATRIX   LocalToWorld4x4;
		DirectX::XMMATRIX   LocalToProjected4x4;
		DirectX::XMMATRIX   WorldToLocal4x4;
		DirectX::XMMATRIX   WorldToView4x4;
		DirectX::XMMATRIX   UvTransform4x4;
		DirectX::XMFLOAT3   EyePosition;
		float               Padding0;
	};

	struct MiscConstants
	{
		MiscConstants()
		{
			static_assert((sizeof(MiscConstants) % 16) == 0, "CB must be 16-byte aligned");
			ViewportWidth = 1.0f;
			ViewportHeight = 1.0f;
			Time = 0.0f;
			Padding1 = 0.0f;
		}

		float ViewportWidth;
		float ViewportHeight;
		float Time;
		float Padding1;
	};

	struct Vertex
	{
		float x, y, z;
		float nx, ny, nz;
		float tx, ty, tz, tw;
		UINT color;
		float u, v;
	};

#define NUM_BONE_INFLUENCES 4
	struct SkinningVertex
	{
		UINT boneIndex[NUM_BONE_INFLUENCES];
		float boneWeight[NUM_BONE_INFLUENCES];
	};
	struct SkinningVertexInput
	{
		byte boneIndex[NUM_BONE_INFLUENCES];
		float boneWeight[NUM_BONE_INFLUENCES];
	};

}