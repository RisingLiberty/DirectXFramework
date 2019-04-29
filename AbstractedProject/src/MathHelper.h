#pragma once

#include <math.h>

using Float2 = XMFLOAT2;
using Float3 = XMFLOAT3;
using Float4 = XMFLOAT4;
using Vector = XMVECTOR;

using Mat3 = XMFLOAT3X3;
using Mat4 = XMFLOAT4X4;

#define VECTOR_2_ZERO Float2(0,0,0)
#define VECTOR_3_ZERO Float3(0,0,0)
#define VECTOR_4_ZERO Float4(0,0,0)

#define MAT_3_IDENTITY DirectX::XMFLOAT3X3\
(\
	1.0f, 0.0f, 0.0f,\
	0.0f, 1.0f, 0.0f,\
	0.0f, 0.0f, 1.0f\
)

#define MAT_4_IDENTITY DirectX::XMFLOAT4X4\
(\
	1.0f, 0.0f, 0.0f, 0.0f,\
	0.0f, 1.0f, 0.0f, 0.0f,\
	0.0f, 0.0f, 1.0f, 0.0f,\
	0.0f, 0.0f, 0.0f, 1.0f\
)

Float2 VectorToFloat2(const Vector& vector);
Float3 VectorToFloat3(const Vector& vector);
Float4 VectorToFloat4(const Vector& vector);

Mat3 MatToFloat3x3(const XMMATRIX& mat);
Mat4 MatToFloat4x4(const XMMATRIX& mat);


