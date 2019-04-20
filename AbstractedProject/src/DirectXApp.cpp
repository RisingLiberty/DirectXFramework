#include "stdafx.h"
#include "DirectXApp.h"
#include "Window.h"
#include "DirectXFactory.h"
#include "Device.h"
#include "Fence.h"
#include "Adapter.h"

#include "CommandQueue.h"
#include "CommandAllocator.h"
#include "CommandList.h"


#include "Utils.h"

namespace
{
	void EnableDebugLayer()
	{
		ComPtr<ID3D12Debug> debugController;
		D3D12GetDebugInterface(IID_PPV_ARGS(debugController.GetAddressOf()));
		debugController->EnableDebugLayer();
	}
}

DirectXApp::DirectXApp(HINSTANCE hInstance):
	m_AppName(L"Direct X App"),
	m_hInstance(hInstance),
	m_Window(nullptr)
{

}

DirectXApp::~DirectXApp()
{

}

HRESULT DirectXApp::Start()
{
	ThrowIfFailedDefault(this->Initialize());

	this->MainLoop();

	return S_OK;
}

HRESULT DirectXApp::Initialize()
{
	m_Factory = std::make_unique<DirectXFactory>();
	m_Window = std::make_unique<Window>(1043, 720, m_AppName, m_Factory->GetFactory());

	ThrowIfFailedDefault(this->InitializeD3D());

	return S_OK;
}

HRESULT DirectXApp::InitializeD3D()
{
	//Initialzing Direct3D begins by creating the Direct3D device. The device represents a display adapter.
	//Usually, the display adapter is a physical piece of 3D hardware(eg. graphics card) however, a systemc an also have a software
	//display adapter that emulates 3D hardware functionality(eg. the WARP adapter). The Direct3D 12 device is used to check feature
	//support, and create all other Direct3D interface objects like resourcees, views and command lists. The device can be created with the following function:
	//pAdapter: specifies the display adapter we want the created device to represent.
	//Specifyinh null fof this parameter uses the primary display adapter. 

	//Enable debug layer
#if defined(DEBUG) || defined (_DEBUG)
	EnableDebugLayer();
#endif

	//pAdapter: Specifies the display adapter we want the created device to represent.
	//Specifying null for this parameter uses the primary display adapter.
	
	//MinimumFeatureLevel: the minimum feature level our application requires support for.
	//device creation will fail if the adapter does not support this feature level.
	
	//riid: the COM ID of the ID3D12Device interface we want to create.
	
	//ppDevice: returns the created device.
	const std::vector<std::unique_ptr<Adapter>>& adapters = m_Window->GetAdapters();
	m_Device = std::make_unique<Device>(adapters.front().get());

	//After we have created our device, we can create our object for CPU/GPU synchronizatino.
	//In addtion, once we get to working with descriptors, we are going to need to know their size.
	//Descriptor sizes can vary across GPUs so we need to query this informatino. We cache the descriptor
	//sizes so that it is available when we need it for various descriptor types.
	m_Fence = std::make_unique<Fence>(0, D3D12_FENCE_FLAG_NONE, m_Device->GetDevice());

	m_RtvDescriptorSize = m_Device->GetRenderTargetViewSize();
	m_DsvDescriptorSize = m_Device->GetDepthStencilViewSize();
	m_CbvSrvUavDescriptorSize = m_Device->GetShaderResourceViewSize();

	//Check 4x MSAA Quality Support
	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;
	msQualityLevels.Format = m_BackBufferFormat;
	msQualityLevels.SampleCount = 4;
	msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	msQualityLevels.NumQualityLevels = 0;

	ThrowIfFailedDevice(m_Device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &msQualityLevels, sizeof(msQualityLevels)));

	m_4xMsaaQuality = msQualityLevels.NumQualityLevels;
	assert(m_4xMsaaQuality > 0 && "Unexpected MSAA quality level");

	// Create command queue and command list.
	ThrowIfFailedDefault(CreateCommandObjects());

	// Create swapchain
	//ThrowIfFailed(CreateSwapChain());

	// Create descriptor heaps
	//ThrowIfFailed(CreateRtvAndDsvDescriptorHeaps());

	//Create render target view
	//First get buffer resources that are stored in the swapchain
	//Buffer: an index identifying the particular back buffer we want to get (in case there's more than one.)
	//riid: The COM ID of the ID#D12Resource interface we want to obtain a pointer to
	//ppSurface: Returns a pointer to an ID3D12Resource that represents the back buffer.
	//HRESULT IDXGISwapChain::GetBuffer(UINT buffer, REFIID riid, void** ppSurface);

	//To create the render target view, we use the ID3D12Device::CreateRenderTargetView method:
	//ID3D12Resource* pResource: Specifies the resource that will be used as the render target.
	//pDesc: A pointer to a D3D12_RENDER_TARGET_VIEW_DESC. ammong other things, this structure describes the
	//data type (format) of the elements in the resource.
	//If the resource was created with a typed format, then this parameter can be null, which indicates
	//to create a view to the first mipmap level of the resource (back buffer only has 1) with the format the
	//resource was created with.
	//DestDescriptor: Handle to the descriptor that will store the created render target view
	//ID3D12Device::CreateRenderTargetView(ID3D12Resource* pResource, const D3D12_RENDER_TARGET_VIEW_DESC *pDesc, D3D12_CPU_DESCRIPTOR_HANDLE DescDescriptor);

	return S_OK;


}

HRESULT DirectXApp::MainLoop()
{
	m_GameTimer.Reset();
	
	bool isRunning = true;

	while (isRunning)
	{
		//if there are window messages then process them.
		if (m_Window->EventLoop() == WM_QUIT)
			isRunning = false;

		m_GameTimer.Tick();
		m_IsPaused = m_Window->IsPaused();

		// everything hat happens in this loop will only happen
		// when the window is active
		if (!m_IsPaused)
		{
			std::cout << "new frame\n";
			this->CalculateFrameStats();
			this->Update(m_GameTimer.GetDeltaTime());
			this->Draw();
		}
		else
			Sleep(100);
	}

	return S_OK;
}

void DirectXApp::Update(const float dTime)
{

}

void DirectXApp::Draw()
{

}

void DirectXApp::CalculateFrameStats() const
{
	//Calculates fps and time it takes to render 1 frame
	static int frameCount = 0;
	static float timeElapsed = 0.0f;

	frameCount++;

	if ((m_GameTimer.GetGameTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCount; //after 1 second, frameCount should hold the number of frames.
		float mspf = 1000.0f / fps;

		std::cout << std::fixed;

		std::cout << "fps: " << fps << "\n";
		std::cout << "mfps: " << mspf << "\n";

		frameCount = 0;
		timeElapsed += 1.0f;
	}
}

HRESULT DirectXApp::CreateCommandObjects()
{
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	m_CommandQueue = std::make_unique<CommandQueue>(m_Device->GetDevice(), queueDesc);
	m_CommandAllocator = std::make_unique<CommandAllocator>(m_Device->GetDevice(), D3D12_COMMAND_LIST_TYPE_DIRECT);

	//We specify null for the pipeline state object parameter.
	m_CommandList = std::make_unique<CommandList>(m_Device->GetDevice(), m_CommandAllocator->GetAllocator(), D3D12_COMMAND_LIST_TYPE_DIRECT, 0);

	//Start off in a closed state.
	//This is because the first time we refer to the command list we will reset it, 
	//and it needs to be closed before calling Reset.
	m_CommandList->Close();

	return S_OK;
}
