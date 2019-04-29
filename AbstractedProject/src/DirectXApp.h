#pragma once

using Viewport = D3D12_VIEWPORT;
using Rect = D3D12_RECT;

#include "GameTimer.h"

class Window;
class DirectXFactory;
class Device;
class Fence;
class CommandQueue;
class CommandAllocator;
class CommandList;
class SwapChain;
class DescriptorHeap;
class Buffer2D;
class FrameResource;

#include "Event.h"
#include "Camera.h"

class DirectXApp
{
public:
	DirectXApp(HINSTANCE hInstance);
	~DirectXApp();

	HRESULT Start();

private:

	HRESULT Initialize();
	HRESULT InitializeD3D();
	void CreateFrameResources();

	HRESULT MainLoop();

	void OnEvent(Event& event);

	void Update(const float dTime);
	void Draw();
	void CalculateFrameStats() const;

	void ConfigureViewport(unsigned int width, unsigned int height);

	HRESULT CreateCommandObjects();
	HRESULT CreateRtvAndDsvDescriptorHeaps();

	void OnResize(const Event& event);

private:
	std::wstring m_AppName;
	HINSTANCE m_hInstance;
	GameTimer m_GameTimer;
	std::unique_ptr<Window> m_Window;
	std::unique_ptr<DirectXFactory> m_Factory;
	std::unique_ptr<Device> m_Device;
	std::unique_ptr<CommandQueue> m_CommandQueue;
	std::unique_ptr<CommandList> m_CommandList;
	std::unique_ptr<SwapChain> m_SwapChain;
	std::unique_ptr<DescriptorHeap> m_DsvHeap;
	std::unique_ptr<Buffer2D> m_DepthStencilBuffer;

	Viewport m_Viewport;
	Rect m_ScissorRect;
	Camera m_Camera;

	UINT m_DsvDescriptorSize;
	UINT m_CbvSrvUavDescriptorSize;

	const DXGI_FORMAT m_BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	UINT m_4xMsaaQuality;

	bool m_IsPaused;

	std::vector<std::unique_ptr<FrameResource>> m_FrameResources;
	unsigned int m_CurrentFrameResourceIndex;
	FrameResource* m_pCurrentFrameResource;

	const unsigned int NUM_FRAME_RESOURCES = 3;
};