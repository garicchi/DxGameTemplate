#pragma once
#include "pch.h"
#include <string>
#include <vector>
#include <map>
#include "Graphics.h"

namespace ToolkitHelper{
	///////////////////////////////////////////////////////////////////////////////////////////
	//
	// Mesh is a class used to display meshes in 3d which are converted
	// during build-time from fbx and dgsl files.
	//
	class Mesh
	{
	public:
		static const UINT MaxTextures = 8;  // 8 unique textures are supported.

		struct SubMesh
		{
			SubMesh() : MaterialIndex(0), IndexBufferIndex(0), VertexBufferIndex(0), StartIndex(0), PrimCount(0) {}

			UINT MaterialIndex;
			UINT IndexBufferIndex;
			UINT VertexBufferIndex;
			UINT StartIndex;
			UINT PrimCount;
		};

		struct Material
		{
			Material() { ZeroMemory(this, sizeof(Material)); }
			~Material() {}

			std::wstring Name;

			DirectX::XMFLOAT4X4 UVTransform;

			float Ambient[4];
			float Diffuse[4];
			float Specular[4];
			float Emissive[4];
			float SpecularPower;

			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Textures[MaxTextures];
			Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader;
			Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader;
			Microsoft::WRL::ComPtr<ID3D11SamplerState> SamplerState;
		};

		struct MeshExtents
		{
			float CenterX, CenterY, CenterZ;
			float Radius;

			float MinX, MinY, MinZ;
			float MaxX, MaxY, MaxZ;
		};

		struct Triangle
		{
			DirectX::XMFLOAT3 points[3];
		};

		typedef std::vector<Triangle> TriangleCollection;

		struct BoneInfo
		{
			std::wstring Name;
			INT ParentIndex;
			DirectX::XMFLOAT4X4 InvBindPos;
			DirectX::XMFLOAT4X4 BindPose;
			DirectX::XMFLOAT4X4 BoneLocalTransform;
		};

		struct Keyframe
		{
			Keyframe() : BoneIndex(0), Time(0.0f) {}

			UINT BoneIndex;
			float Time;
			DirectX::XMFLOAT4X4 Transform;
		};

		typedef std::vector<Keyframe> KeyframeArray;

		struct AnimClip
		{
			float StartTime;
			float EndTime;
			KeyframeArray Keyframes;
		};

		typedef std::map<const std::wstring, AnimClip> AnimationClipMap;

		// Access to mesh data.
		std::vector<SubMesh>& SubMeshes() { return m_submeshes; }
		std::vector<Material>& Materials() { return m_materials; }
		std::vector<ID3D11Buffer*>& VertexBuffers() { return m_vertexBuffers; }
		std::vector<ID3D11Buffer*>& SkinningVertexBuffers() { return m_skinningVertexBuffers; }
		std::vector<ID3D11Buffer*>& IndexBuffers() { return m_indexBuffers; }
		MeshExtents& Extents() { return m_meshExtents; }
		AnimationClipMap& AnimationClips() { return m_animationClips; }
		std::vector<BoneInfo>& BoneInfoCollection() { return m_boneInfo; }
		TriangleCollection& Triangles() { return m_triangles; }
		const wchar_t* Name() const { return m_name.c_str(); }

		void* Tag;

		// Destructor.
		~Mesh()
		{
			for (ID3D11Buffer *ib : m_indexBuffers)
			{
				SafeRelease(ib);
			}

			for (ID3D11Buffer *vb : m_vertexBuffers)
			{
				SafeRelease(vb);
			}

			for (ID3D11Buffer *svb : m_skinningVertexBuffers)
			{
				SafeRelease(svb);
			}

			m_submeshes.clear();
			m_materials.clear();
			m_indexBuffers.clear();
			m_vertexBuffers.clear();
			m_skinningVertexBuffers.clear();
		}

		// Render the mesh to the current render target.
		void Render(const Graphics& graphics, const DirectX::XMMATRIX& world)
		{
			ID3D11DeviceContext* deviceContext = graphics.GetDeviceContext();

			BOOL supportsShaderResources = graphics.GetDeviceFeatureLevel() >= D3D_FEATURE_LEVEL_10_0;

			const DirectX::XMMATRIX& view = DirectX::XMLoadFloat4x4(&graphics.GetCamera().GetView());
			const DirectX::XMMATRIX& projection = DirectX::XMLoadFloat4x4(&graphics.GetCamera().GetProjection()) * DirectX::XMLoadFloat4x4(&graphics.GetCamera().GetOrientationMatrix());

			// Compute the object matrices.
			DirectX::XMMATRIX localToView = world * view;
			DirectX::XMMATRIX localToProj = world * view * projection;

			// Initialize object constants and update the constant buffer.
			ObjectConstants objConstants;
			objConstants.LocalToWorld4x4 = DirectX::XMMatrixTranspose(world);
			objConstants.LocalToProjected4x4 = DirectX::XMMatrixTranspose(localToProj);
			objConstants.WorldToLocal4x4 = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, world));
			objConstants.WorldToView4x4 = DirectX::XMMatrixTranspose(view);
			objConstants.UvTransform4x4 = DirectX::XMMatrixIdentity();
			objConstants.EyePosition = graphics.GetCamera().GetPosition();
			graphics.UpdateObjectConstants(objConstants);

			// Assign the constant buffers to correct slots.
			ID3D11Buffer* constantBuffer = graphics.GetLightConstants();
			deviceContext->VSSetConstantBuffers(1, 1, &constantBuffer);
			deviceContext->PSSetConstantBuffers(1, 1, &constantBuffer);

			constantBuffer = graphics.GetMiscConstants();
			deviceContext->VSSetConstantBuffers(3, 1, &constantBuffer);
			deviceContext->PSSetConstantBuffers(3, 1, &constantBuffer);

			// Prepare to draw.
			deviceContext->IASetInputLayout(graphics.GetVertexInputLayout());
			deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			// Loop over each submesh.
			for (SubMesh& submesh : m_submeshes)
			{
				// Only draw submeshes that have valid materials.
				MaterialConstants materialConstants;

				if (submesh.IndexBufferIndex < m_indexBuffers.size() &&
					submesh.VertexBufferIndex < m_vertexBuffers.size())
				{
					UINT stride = sizeof(Vertex);
					UINT offset = 0;
					deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffers[submesh.VertexBufferIndex], &stride, &offset);
					deviceContext->IASetIndexBuffer(m_indexBuffers[submesh.IndexBufferIndex], DXGI_FORMAT_R16_UINT, 0);
				}

				if (submesh.MaterialIndex < m_materials.size())
				{
					Material& material = m_materials[submesh.MaterialIndex];

					// Update the material constant buffer.
					memcpy(&materialConstants.Ambient, material.Ambient, sizeof(material.Ambient));
					memcpy(&materialConstants.Diffuse, material.Diffuse, sizeof(material.Diffuse));
					memcpy(&materialConstants.Specular, material.Specular, sizeof(material.Specular));
					memcpy(&materialConstants.Emissive, material.Emissive, sizeof(material.Emissive));
					materialConstants.SpecularPower = material.SpecularPower;

					graphics.UpdateMaterialConstants(materialConstants);

					// Assign the material buffer to correct slots.
					constantBuffer = graphics.GetMaterialConstants();
					deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
					deviceContext->PSSetConstantBuffers(0, 1, &constantBuffer);

					// Update the UV transform.
					memcpy(&objConstants.UvTransform4x4, &material.UVTransform, sizeof(objConstants.UvTransform4x4));
					graphics.UpdateObjectConstants(objConstants);

					constantBuffer = graphics.GetObjectConstants();
					deviceContext->VSSetConstantBuffers(2, 1, &constantBuffer);
					deviceContext->PSSetConstantBuffers(2, 1, &constantBuffer);

					// Assign the shaders, samplers and texture resources.
					ID3D11SamplerState* sampler = material.SamplerState.Get();

					deviceContext->VSSetShader(material.VertexShader.Get(), nullptr, 0);
					if (supportsShaderResources)
					{
						deviceContext->VSSetSamplers(0, 1, &sampler);
					}

					deviceContext->PSSetShader(material.PixelShader.Get(), nullptr, 0);
					deviceContext->PSSetSamplers(0, 1, &sampler);

					for (UINT tex = 0; tex < MaxTextures; tex++)
					{
						ID3D11ShaderResourceView* texture = material.Textures[tex].Get();

						if (supportsShaderResources)
						{
							deviceContext->VSSetShaderResources(0 + tex, 1, &texture);
							deviceContext->VSSetShaderResources(MaxTextures + tex, 1, &texture);
						}

						deviceContext->PSSetShaderResources(0 + tex, 1, &texture);
						deviceContext->PSSetShaderResources(MaxTextures + tex, 1, &texture);
					}

					// Draw the submesh.
					deviceContext->DrawIndexed(submesh.PrimCount * 3, submesh.StartIndex, 0);
				}
			}
		}

		// Loads a scene from the specified file, returning a vector of mesh objects.
		static concurrency::task<void> LoadFromFileAsync(
			Graphics& graphics,
			const std::wstring& meshFilename,
			const std::wstring& shaderPathLocation,
			const std::wstring& texturePathLocation,
			std::vector<Mesh*>& loadedMeshes,
			bool clearLoadedMeshesVector = true
			)
		{
			// Clear the output vector.
			if (clearLoadedMeshesVector)
			{
				loadedMeshes.clear();
			}

			auto folder = Windows::ApplicationModel::Package::Current->InstalledLocation;

			// Start by loading the file.
			return concurrency::create_task(folder->GetFileAsync(Platform::StringReference(meshFilename.c_str())))
				// Then open the file.
				.then([](Windows::Storage::StorageFile^ file)
			{
				return Windows::Storage::FileIO::ReadBufferAsync(file);
			})
				// Then read the meshes.
				.then([&graphics, shaderPathLocation, texturePathLocation, &loadedMeshes](Windows::Storage::Streams::IBuffer^ buffer)
			{
				auto reader = Windows::Storage::Streams::DataReader::FromBuffer(buffer);
				reader->ByteOrder = Windows::Storage::Streams::ByteOrder::LittleEndian;
				reader->UnicodeEncoding = Windows::Storage::Streams::UnicodeEncoding::Utf8;

				// Read how many meshes are part of the scene.
				std::shared_ptr<UINT> remainingMeshesToRead = std::make_shared<UINT>(reader->ReadUInt32());

				if (*remainingMeshesToRead == 0)
				{
					return concurrency::create_task([](){});
				}

				// For each mesh in the scene, load it from the file.

				return concurrency::extras::create_iterative_task([reader, &graphics, shaderPathLocation, texturePathLocation, &loadedMeshes, remainingMeshesToRead]()
				{
					return Mesh::ReadAsync(reader, graphics, shaderPathLocation, texturePathLocation)
						.then([&loadedMeshes, remainingMeshesToRead](Mesh* mesh) -> bool
					{
						if (mesh != nullptr)
						{
							loadedMeshes.push_back(mesh);
						}

						// Return true to continue iterating, false to stop.

						*remainingMeshesToRead = *remainingMeshesToRead - 1;

						return *remainingMeshesToRead > 0;
					});
				});
			});
		}

	private:
		Mesh()
		{
			Tag = nullptr;
		}

		static void StripPath(std::wstring& path)
		{
			size_t p = path.rfind(L"\\");
			if (p != std::wstring::npos)
			{
				path = path.substr(p + 1);
			}
		}

		template <typename T>
		static void ReadStruct(Windows::Storage::Streams::DataReader^ reader, T* output, size_t size = sizeof(T))
		{
			reader->ReadBytes(Platform::ArrayReference<BYTE>((BYTE*) output, size));
		}

		// Reads a string converted from an array of wchar_t of given size using a DataReader.
		static void ReadString(Windows::Storage::Streams::DataReader^ reader, std::wstring* output, unsigned int count)
		{
			if (count == 0)
			{
				return;
			}

			std::vector<wchar_t> characters(count);
			ReadStruct(reader, &characters[0], count * sizeof(wchar_t));
			*output = &characters[0];
		}

		// Reads a string converted from an array of wchar_t using a DataReader.
		static void ReadString(Windows::Storage::Streams::DataReader^ reader, std::wstring* output)
		{
			UINT count = reader->ReadUInt32();
			ReadString(reader, output, count);
		}

		static concurrency::task<Mesh*> ReadAsync(Windows::Storage::Streams::DataReader^ reader, Graphics& graphics, const std::wstring& shaderPathLocation, const std::wstring& texturePathLocation)
		{
			std::vector<concurrency::task<void>> innerTasks;

			// Initialize output mesh.
			if (reader == nullptr)
			{
				return concurrency::extras::create_value_task<Mesh*>(nullptr);
			}

			Mesh* mesh = new Mesh();

			ReadString(reader, &mesh->m_name);

			// Read material count.
			UINT numMaterials = reader->ReadUInt32();
			mesh->m_materials.resize(numMaterials);

			// Load each material.
			for (UINT i = 0; i < numMaterials; i++)
			{
				Material& material = mesh->m_materials[i];

				// Read the material name.
				ReadString(reader, &material.Name);

				// Read the ambient and diffuse properties of material.

				ReadStruct(reader, &material.Ambient, sizeof(material.Ambient));
				ReadStruct(reader, &material.Diffuse, sizeof(material.Diffuse));
				ReadStruct(reader, &material.Specular, sizeof(material.Specular));
				ReadStruct(reader, &material.SpecularPower);
				ReadStruct(reader, &material.Emissive, sizeof(material.Emissive));
				ReadStruct(reader, &material.UVTransform);

				// Assign the vertex shader and sampler state.
				material.VertexShader = graphics.GetVertexShader();

				material.SamplerState = graphics.GetSamplerState();

				// Read the size of the name of the pixel shader.
				UINT stringLen = reader->ReadUInt32();
				if (stringLen > 0)
				{
					// Read the pixel shader name.
					std::wstring sourceFile;
					ReadString(reader, &sourceFile, stringLen);

					// Continue loading pixel shader if name is not empty.
					if (!sourceFile.empty())
					{
						// Create well-formed file name for the pixel shader.
						Mesh::StripPath(sourceFile);

						// Use fallback shader if Pixel Shader Model 4.0 is not supported.
						if (graphics.GetDeviceFeatureLevel() < D3D_FEATURE_LEVEL_10_0)
						{
							// This device is not compatible with Pixel Shader Model 4.0.
							// Try to fall back to a shader with the same name but compiled from HLSL.
							size_t lastUnderline = sourceFile.find_last_of('_');
							size_t firstDotAfterLastUnderline = sourceFile.find_first_of('.', lastUnderline);
							sourceFile = sourceFile.substr(lastUnderline + 1, firstDotAfterLastUnderline - lastUnderline) + L"cso";
						}

						// Append the base path.
						sourceFile = shaderPathLocation + sourceFile;

						// Get or create the pixel shader.
						innerTasks.push_back(graphics.GetOrCreatePixelShaderAsync(sourceFile).then([&material](ID3D11PixelShader* materialPixelShader)
						{
							material.PixelShader = materialPixelShader;
						}));
					}
				}

				// Load the textures.
				for (int t = 0; t < MaxTextures; t++)
				{
					// Read the size of the name of the texture.
					stringLen = reader->ReadUInt32();
					if (stringLen > 0)
					{
						// Read the texture name.
						std::wstring sourceFile;
						ReadString(reader, &sourceFile, stringLen);

						// Append the base path.
						sourceFile = texturePathLocation + sourceFile;

						// Get or create the texture.
						innerTasks.push_back(graphics.GetOrCreateTextureAsync(sourceFile).then([&material, t](ID3D11ShaderResourceView* textureResource)
						{
							material.Textures[t] = textureResource;
						}));
					}
				}
			}

			// Does this object contain skeletal animation?
			BYTE isSkeletalDataPresent = reader->ReadByte();

			// Read the submesh information.
			UINT numSubmeshes = reader->ReadUInt32();
			mesh->m_submeshes.resize(numSubmeshes);
			for (UINT i = 0; i < numSubmeshes; i++)
			{
				SubMesh& submesh = mesh->m_submeshes[i];
				submesh.MaterialIndex = reader->ReadUInt32();
				submesh.IndexBufferIndex = reader->ReadUInt32();
				submesh.VertexBufferIndex = reader->ReadUInt32();
				submesh.StartIndex = reader->ReadUInt32();
				submesh.PrimCount = reader->ReadUInt32();
			}

			// Read the index buffers.
			UINT numIndexBuffers = reader->ReadUInt32();
			mesh->m_indexBuffers.resize(numIndexBuffers);

			std::vector<std::vector<USHORT>> indexBuffers(numIndexBuffers);

			for (UINT i = 0; i < numIndexBuffers; i++)
			{
				UINT ibCount = reader->ReadUInt32();
				if (ibCount > 0)
				{
					indexBuffers[i].resize(ibCount);

					// Read in the index data.
					for (USHORT& component : indexBuffers[i])
					{
						component = reader->ReadUInt16();
					}

					// Create an index buffer for this data.
					D3D11_BUFFER_DESC bd = { 0 };
					bd.Usage = D3D11_USAGE_DEFAULT;
					bd.ByteWidth = sizeof(USHORT)* ibCount;
					bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
					bd.CPUAccessFlags = 0;

					D3D11_SUBRESOURCE_DATA initData = { 0 };
					initData.pSysMem = &indexBuffers[i][0];

					graphics.GetDevice()->CreateBuffer(&bd, &initData, &mesh->m_indexBuffers[i]);
				}
			}

			// Read the vertex buffers.
			UINT numVertexBuffers = reader->ReadUInt32();
			mesh->m_vertexBuffers.resize(numVertexBuffers);

			std::vector<std::vector<Vertex>> vertexBuffers(numVertexBuffers);

			for (UINT i = 0; i < numVertexBuffers; i++)
			{
				UINT vbCount = reader->ReadUInt32();
				if (vbCount > 0)
				{
					vertexBuffers[i].resize(vbCount);

					// Read in the vertex data.
					ReadStruct(reader, &vertexBuffers[i][0], vbCount * sizeof(Vertex));

					// Create a vertex buffer for this data.
					D3D11_BUFFER_DESC bd = { 0 };
					bd.Usage = D3D11_USAGE_DEFAULT;
					bd.ByteWidth = sizeof(Vertex)* vbCount;
					bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
					bd.CPUAccessFlags = 0;

					D3D11_SUBRESOURCE_DATA initData = { 0 };
					initData.pSysMem = &vertexBuffers[i][0];

					graphics.GetDevice()->CreateBuffer(&bd, &initData, &mesh->m_vertexBuffers[i]);
				}
			}

			// Create the triangle array for each submesh.
			for (SubMesh& subMesh : mesh->m_submeshes)
			{
				std::vector<USHORT>& ib = indexBuffers[subMesh.IndexBufferIndex];
				std::vector<Vertex>& vb = vertexBuffers[subMesh.VertexBufferIndex];

				for (UINT j = 0; j < ib.size(); j += 3)
				{
					Vertex& v0 = vb[ib[j]];
					Vertex& v1 = vb[ib[j + 1]];
					Vertex& v2 = vb[ib[j + 2]];

					Triangle tri;
					tri.points[0].x = v0.x;
					tri.points[0].y = v0.y;
					tri.points[0].z = v0.z;

					tri.points[1].x = v1.x;
					tri.points[1].y = v1.y;
					tri.points[1].z = v1.z;

					tri.points[2].x = v2.x;
					tri.points[2].y = v2.y;
					tri.points[2].z = v2.z;

					mesh->m_triangles.push_back(tri);
				}
			}

			// Clear the temporary buffers.
			vertexBuffers.clear();
			indexBuffers.clear();

			// Read the skinning vertex buffers.
			UINT numSkinningVertexBuffers = reader->ReadUInt32();
			mesh->m_skinningVertexBuffers.resize(numSkinningVertexBuffers);
			for (UINT i = 0; i < numSkinningVertexBuffers; i++)
			{
				UINT vbCount = reader->ReadUInt32();
				if (vbCount > 0)
				{
					std::vector<SkinningVertexInput> verts(vbCount);

					// Read in the vertex data.
					for (SkinningVertexInput& vertex : verts)
					{
						for (size_t j = 0; j < NUM_BONE_INFLUENCES; j++)
						{
							// Convert indices to byte (to support D3D Feature Level 9).
							vertex.boneIndex[j] = (byte) reader->ReadUInt32();
						}
						for (size_t j = 0; j < NUM_BONE_INFLUENCES; j++)
						{
							vertex.boneWeight[j] = reader->ReadSingle();
						}
					}

					// Create a vertex buffer for this data.
					D3D11_BUFFER_DESC bd = { 0 };
					bd.Usage = D3D11_USAGE_DEFAULT;
					bd.ByteWidth = sizeof(SkinningVertexInput)* vbCount;
					bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
					bd.CPUAccessFlags = 0;

					D3D11_SUBRESOURCE_DATA initData = { 0 };
					initData.pSysMem = &verts[0];

					graphics.GetDevice()->CreateBuffer(&bd, &initData, &mesh->m_skinningVertexBuffers[i]);
				}
			}

			// Read the mesh extents.
			ReadStruct(reader, &mesh->m_meshExtents);

			// Read bones and animation information if needed.
			if (isSkeletalDataPresent)
			{
				// Read bone information.
				UINT boneCount = reader->ReadUInt32();

				mesh->m_boneInfo.resize(boneCount);

				for (BoneInfo& bone : mesh->m_boneInfo)
				{
					// Read the bone name.
					ReadString(reader, &bone.Name);

					// Read the transforms.
					bone.ParentIndex = reader->ReadInt32();
					ReadStruct(reader, &bone.InvBindPos);
					ReadStruct(reader, &bone.BindPose);
					ReadStruct(reader, &bone.BoneLocalTransform);
				}

				// Read animation clips.
				UINT clipCount = reader->ReadUInt32();

				for (UINT j = 0; j < clipCount; j++)
				{
					// Read clip name.
					std::wstring clipName;
					ReadString(reader, &clipName);

					mesh->m_animationClips[clipName].StartTime = reader->ReadSingle();
					mesh->m_animationClips[clipName].EndTime = reader->ReadSingle();

					KeyframeArray& keyframes = mesh->m_animationClips[clipName].Keyframes;

					// Read keyframe count.
					UINT kfCount = reader->ReadUInt32();

					// Preallocate the memory.
					keyframes.reserve(kfCount);

					// Read each keyframe.
					for (UINT k = 0; k < kfCount; k++)
					{
						Keyframe kf;

						// Read the bone.
						kf.BoneIndex = reader->ReadUInt32();

						// Read the time.
						kf.Time = reader->ReadSingle();

						// Read the transform.
						ReadStruct(reader, &kf.Transform);

						// Add to the keyframe collection.
						keyframes.push_back(kf);
					}
				}
			}

			return concurrency::when_all(innerTasks.begin(), innerTasks.end()).then([mesh]()
			{
				return mesh;
			});
		}

		std::vector<SubMesh> m_submeshes;
		std::vector<Material> m_materials;
		std::vector<ID3D11Buffer*> m_vertexBuffers;
		std::vector<ID3D11Buffer*> m_skinningVertexBuffers;
		std::vector<ID3D11Buffer*> m_indexBuffers;
		TriangleCollection m_triangles;

		MeshExtents m_meshExtents;

		AnimationClipMap m_animationClips;
		std::vector<BoneInfo> m_boneInfo;

		std::wstring m_name;
	};
	//
	//
	///////////////////////////////////////////////////////////////////////////////////////////

}