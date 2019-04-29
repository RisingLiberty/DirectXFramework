#pragma once

#define MaxLights 16

struct ObjectConstants
{
	Mat4 World = MAT_4_IDENTITY;

	//Mat4 TexTransform = MAT_4_IDENTITY;
};

struct Light
{
	Float3 Color;		// Light color
	float FalloffStart;	// Points/Spot light only
	Float3 Direction;	// Directional/Spot light only
	float FalloffEnd;	// Point/Spot light only
	Float3 Position;	// Points/Spot light only
	float SpotPower;	// Spot light only
};

// Contains constant data that is fixed over a given rendering pass.
struct PassConstants
{
	Mat4 View			= MAT_4_IDENTITY;
	Mat4 InvView		= MAT_4_IDENTITY;
	Mat4 Proj			= MAT_4_IDENTITY;
	Mat4 InvProj		= MAT_4_IDENTITY;
	Mat4 ViewProj		= MAT_4_IDENTITY;
	Mat4 InvViewProj	= MAT_4_IDENTITY;
	
	Float3 EyePosW = { 0.0f, 0.0f, 0.0f };
	float Pad1 = 0.0f; // Pad because Direct X is 16 byte alligned
	
	Float2 RenderTargetSize = { 0.0f, 0.0f };
	Float2 InvRenderTargetSize = { 0.0f, 0.0f };
	
	float NearZ = 0.0f;
	float FarZ = 0.0f;
	float TotalTime = 0.0f;
	float DeltaTime = 0.0f;

	//Since lightning
	Float4 AmbientLight = { 0.0f, 0.0f, 0.0f, 1.0f };

	// Indices [0, NUM_DIR_LIGHTS) are directional lights;
	// indices [NUM_DIR_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHTS) are point lights;
	// indices [NUM_DIR_LIGHTS+NUM_POINT_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHT+NUM_SPOT_LIGHTS)
	// are spot lights for a maximum of MaxLights per object.
	Light Lights[MaxLights];
};

struct MaterialConstants
{
	Float4 DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
	Float3 FresnelR0 = { 0.01f, 0.01f, 0.01f };

	float Roughness = 0.25f;

	Mat4 MatTransform = MAT_4_IDENTITY;
};