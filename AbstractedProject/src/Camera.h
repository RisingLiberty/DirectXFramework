#pragma once

class Camera
{
public:
	Camera(const Float3& position, const float theta, const float phi, const float radius, const XMVECTOR& target = XMVectorZero(), const XMVECTOR& up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f));
	Camera(const Float3& position, const Vector& target, const Vector& up);
	Camera(const Vector& position, const Vector& target, const Vector& up);

	void Update();

	Float3 GetPosition() const;
	float GetTheta() const;
	float GetPhi() const;
	float GetRadius() const;
	Mat4 GetViewMatrix() const;

	void SetPosition(const Float3& newPosition);
	void SetTheta(float newTheta);
	void SetPhi(float newPhi);
	void SetRadius(float newRadius);

	void AddToPosition(const Float3& deltaPosition);
	void AddToTheta(float deltaTheta);
	void AddToPhi(float deltaPhi);
	void AddToRadius(float deltaRadius);

private:
	Mat4 m_ViewMat;
	Float3 m_Position;
	float m_Theta;
	float m_Phi;
	float m_Radius;
};