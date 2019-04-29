#include "stdafx.h"
#include "Math.h"

Float2 VectorToFloat2(const Vector& vector)
{
	Float2 v;
	XMStoreFloat2(&v, vector);
	return v;
}

Float3 VectorToFloat3(const Vector& vector)
{
	Float3 v;
	XMStoreFloat3(&v, vector);
	return v;
}

Float4 VectorToFloat4(const Vector& vector)
{
	Float4 v;
	XMStoreFloat4(&v, vector);
	return v;
}

Mat3 MatToFloat3x3(const XMMATRIX& mat)
{
	Mat3 matrix;
	XMStoreFloat3x3(&matrix, mat);
	return matrix;
}

Mat4 MatToFloat4x4(const XMMATRIX& mat)
{
	Mat4 matrix;
	XMStoreFloat4x4(&matrix, mat);
	return matrix;
}

