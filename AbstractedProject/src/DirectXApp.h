#pragma once

#include "GameTimer.h"

class Window;
class DirectXFactory;
class Device;
class Fence;
class CommandQueue;
class CommandAllocator;
class CommandList;


class DirectXApp
{
public:
	DirectXApp(HINSTANCE hInstance);
	~DirectXApp();

	HRESULT Start();

private:

	HRESULT Initialize();
	HRESULT InitializeD3D();

	HRESULT MainLoop();

	void Update(const float dTime);
	void Draw();
	void CalculateFrameStats() const;

	HRESULT CreateCommandObjects();

private:
	std::wstring m_AppName;
	HINSTANCE m_hInstance;
	GameTimer m_GameTimer;
	std::unique_ptr<Window> m_Window;
	std::unique_ptr<DirectXFactory> m_Factory;
	std::unique_ptr<Device> m_Device;
	std::unique_ptr<Fence> m_Fence;
	std::unique_ptr<CommandQueue> m_CommandQueue;
	std::unique_ptr<CommandAllocator> m_CommandAllocator;
	std::unique_ptr<CommandList> m_CommandList;


	UINT m_RtvDescriptorSize;
	UINT m_DsvDescriptorSize;
	UINT m_CbvSrvUavDescriptorSize;

	const DXGI_FORMAT m_BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	UINT m_4xMsaaQuality;

	bool m_IsPaused;
};