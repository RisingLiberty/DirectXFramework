#include "stdafx.h"
#include "Camera.h"

Camera::Camera(const Float3& position, const float theta, const float phi, const float radius, const XMVECTOR& target, const XMVECTOR& up):
	m_Position(position),
	m_Theta(theta),
	m_Phi(phi),
	m_Radius(radius)
{
	XMVECTOR pos = XMVectorSet(position.x, position.y, position.z, 1.0f);

	XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
	m_ViewMat = MatToFloat4x4(view);
}

Camera::Camera(const Float3& position, const Vector& target, const Vector& up) :
	m_Position(position),
	m_Theta(0),
	m_Phi(0),
	m_Radius(0)
{
	Vector pos = XMLoadFloat3(&position);
	XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
	m_ViewMat = MatToFloat4x4(view);
}

Camera::Camera(const Vector& position, const Vector& target, const Vector& up) :
	m_Position(VectorToFloat3(position)),
	m_Theta(0),
	m_Phi(0),
	m_Radius(0)
{
	XMMATRIX view = XMMatrixLookAtLH(position, target, up);
	m_ViewMat = MatToFloat4x4(view);
}

void Camera::Update()
{
	m_Position.x = m_Radius * sinf(m_Phi)*cosf(m_Theta);
	m_Position.z = m_Radius * sinf(m_Phi)*sinf(m_Theta);
	m_Position.y = m_Radius * cosf(m_Phi);

	// Build the view matrix
	XMVECTOR pos = XMVectorSet(m_Position.x, m_Position.y, m_Position.z, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
	XMStoreFloat4x4(&m_ViewMat, view);
}

Float3 Camera::GetPosition() const
{
	return m_Position;
}

float Camera::GetTheta() const
{
	return m_Theta;
}

float Camera::GetPhi() const
{
	return m_Phi;
}

float Camera::GetRadius() const
{
	return m_Radius;
}

Mat4 Camera::GetViewMatrix() const
{
	return m_ViewMat;
}

void Camera::SetPosition(const Float3 & newPosition)
{
	m_Position = newPosition;
}

void Camera::SetTheta(float newTheta)
{
	m_Theta = newTheta;
}

void Camera::SetPhi(float newPhi)
{
	m_Phi = newPhi;
}

void Camera::SetRadius(float newRadius)
{
	m_Radius = newRadius;
}

void Camera::AddToPosition(const Float3& deltaPosition)
{
	m_Position.x += deltaPosition.x;
	m_Position.y += deltaPosition.y;
	m_Position.z += deltaPosition.z;
}

void Camera::AddToTheta(float deltaTheta)
{
	m_Theta += deltaTheta;
}

void Camera::AddToPhi(float deltaPhi)
{
	m_Phi += deltaPhi;
}

void Camera::AddToRadius(float deltaRadius)
{
	m_Radius += deltaRadius;
}
