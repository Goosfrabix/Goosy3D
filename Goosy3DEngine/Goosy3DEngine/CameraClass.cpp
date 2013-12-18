////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Cameraclass.h"

CameraClass::CameraClass()
{
	m_position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rotation = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_lookAt = D3DXVECTOR3(0.0f,0.0f,1.0f);
	m_upVector = D3DXVECTOR3(0.0f,1.0f,0.0f);
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}

void CameraClass::SetPosition(D3DXVECTOR3& pos)
{
	m_position = pos;
	return;
}


void CameraClass::SetRotation(D3DXVECTOR3& rot)
{
	m_rotation = rot;
	return;
}

void CameraClass::SetLookAt(D3DXVECTOR3& lkat)
{
	m_lookAt = lkat;
	return;
}
void CameraClass::SetUpVector(D3DXVECTOR3& upv)
{
	m_upVector = upv;
	return;
}

D3DXVECTOR3 CameraClass::GetPosition()
{
	return m_position;
}


D3DXVECTOR3 CameraClass::GetRotation()
{
	return m_rotation;
}

D3DXVECTOR3 CameraClass::GetLookAt()
{
	return m_lookAt;
}
D3DXVECTOR3 CameraClass::GetUpVector()
{
	return m_upVector;
}

void CameraClass::Render()
{
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;


	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotation.x * 0.0174532925f;
	yaw   = m_rotation.y * 0.0174532925f;
	roll  = m_rotation.z * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&m_lookAt, &m_lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&m_upVector, &m_upVector, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	m_lookAt = m_position + m_lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &m_lookAt, &m_upVector);

	return;
}

void CameraClass::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}