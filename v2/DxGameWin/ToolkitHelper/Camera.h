#pragma once
#include "pch.h"

///////////////////////////////////////////////////////////////////////////////////////////
//
// Camera class provides simple camera functionality.
//
namespace ToolkitHelper{

	class Camera
	{
	public:
		Camera()
		{
			DirectX::XMMATRIX identity = DirectX::XMMatrixIdentity();
			DirectX::XMStoreFloat4x4(&m_view, identity);
			DirectX::XMStoreFloat4x4(&m_proj, identity);

			m_viewWidth = 1;
			m_viewHeight = 1;

			m_position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			m_lookAt = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
			m_up = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
		}

		const DirectX::XMFLOAT4X4& GetView() const { return m_view; }
		const DirectX::XMFLOAT4X4& GetProjection() const { return m_proj; }
		const DirectX::XMFLOAT4X4& GetOrientationMatrix() const { return m_orientationMatrix; }

		const DirectX::XMFLOAT3& GetPosition() const { return m_position; }
		const DirectX::XMFLOAT3& GetLookAt() const { return m_lookAt; }
		const DirectX::XMFLOAT3& GetUpVector() const { return m_up; }

		void SetViewport(UINT w, UINT h)
		{
			m_viewWidth = w;
			m_viewHeight = h;
		}

		void SetProjection(float fovY, float aspect, float zn, float zf)
		{
			DirectX::XMMATRIX p = DirectX::XMMatrixPerspectiveFovRH(fovY, aspect, zn, zf);
			XMStoreFloat4x4(&m_proj, p);
		}

		void SetProjectionOrthographic(float viewWidth, float viewHeight, float zn, float zf)
		{
			DirectX::XMMATRIX p = DirectX::XMMatrixOrthographicRH(viewWidth, viewHeight, zn, zf);
			XMStoreFloat4x4(&m_proj, p);
		}

		void SetProjectionOrthographicOffCenter(float viewLeft, float viewRight, float viewBottom, float viewTop, float zn, float zf)
		{
			DirectX::XMMATRIX p = DirectX::XMMatrixOrthographicOffCenterRH(viewLeft, viewRight, viewBottom, viewTop, zn, zf);
			XMStoreFloat4x4(&m_proj, p);
		}

		void SetPosition(const DirectX::XMFLOAT3& position)
		{
			m_position = position;
			this->UpdateView();
		}

		void SetLookAt(const DirectX::XMFLOAT3& lookAt)
		{
			m_lookAt = lookAt;
			this->UpdateView();
		}

		void SetUpVector(const DirectX::XMFLOAT3& up)
		{
			m_up = up;
			this->UpdateView();
		}

		void SetOrientationMatrix(const DirectX::XMFLOAT4X4& orientationMatrix)
		{
			m_orientationMatrix = orientationMatrix;
		}

		void GetWorldLine(UINT pixelX, UINT pixelY, DirectX::XMFLOAT3* outPoint, DirectX::XMFLOAT3* outDir)
		{
			DirectX::XMFLOAT4 p0 = DirectX::XMFLOAT4((float) pixelX, (float) pixelY, 0, 1);
			DirectX::XMFLOAT4 p1 = DirectX::XMFLOAT4((float) pixelX, (float) pixelY, 1, 1);

			DirectX::XMVECTOR screen0 = DirectX::XMLoadFloat4(&p0);
			DirectX::XMVECTOR screen1 = DirectX::XMLoadFloat4(&p1);

			DirectX::XMMATRIX projMat = XMLoadFloat4x4(&m_proj);
			DirectX::XMMATRIX viewMat = XMLoadFloat4x4(&m_view);

			DirectX::XMVECTOR pp0 = DirectX::XMVector3Unproject(screen0, 0, 0, (float) m_viewWidth, (float) m_viewHeight, 0, 1, projMat, viewMat, DirectX::XMMatrixIdentity());
			DirectX::XMVECTOR pp1 = DirectX::XMVector3Unproject(screen1, 0, 0, (float) m_viewWidth, (float) m_viewHeight, 0, 1, projMat, viewMat, DirectX::XMMatrixIdentity());

			DirectX::XMStoreFloat3(outPoint, pp0);
			DirectX::XMStoreFloat3(outDir, pp1);

			outDir->x -= outPoint->x;
			outDir->y -= outPoint->y;
			outDir->z -= outPoint->z;
		}

	private:
		void UpdateView()
		{
			DirectX::XMVECTOR vPosition = DirectX::XMLoadFloat3(&m_position);
			DirectX::XMVECTOR vLook = DirectX::XMLoadFloat3(&m_lookAt);
			DirectX::XMVECTOR vUp = DirectX::XMLoadFloat3(&m_up);

			DirectX::XMMATRIX v = DirectX::XMMatrixLookAtRH(vPosition, vLook, vUp);
			DirectX::XMStoreFloat4x4(&m_view, v);
		}

		DirectX::XMFLOAT4X4 m_view;
		DirectX::XMFLOAT4X4 m_proj;
		DirectX::XMFLOAT4X4 m_orientationMatrix;
		DirectX::XMFLOAT3 m_position;
		DirectX::XMFLOAT3 m_lookAt;
		DirectX::XMFLOAT3 m_up;
		UINT m_viewWidth;
		UINT m_viewHeight;
	};

}