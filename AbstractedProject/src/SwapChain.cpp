#include "stdafx.h"
#include "SwapChain.h"

#include "Window.h"
#include "Texture.h"
#include "DescriptorHeap.h"
#include "Device.h"

SwapChain::SwapChain(Device* pDevice, IDXGIFactory1* pFactory, ID3D12CommandQueue* pCommandQueue, Window* pWindow, int refreshRateNumerator, DXGI_FORMAT format):
	m_Format(format),
	m_CurrentBackBuffer(0)
{
	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = pWindow->GetWidth();
	sd.BufferDesc.Height = pWindow->GetHeight();
	sd.BufferDesc.RefreshRate.Numerator = refreshRateNumerator;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = format;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = 1; //MSAA not directly supported in DX12
	sd.SampleDesc.Quality = 0; //MSAA not directly supported in DX12
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // we're rendering to this buffer
	sd.BufferCount = BUFFER_COUNT; //Double buffering
	sd.OutputWindow = pWindow->GetHandle();
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	ThrowIfFailedCommandQueue(pFactory->CreateSwapChain(pCommandQueue, &sd, m_SwapChain.ReleaseAndGetAddressOf()));

	DescriptorHeapDesc rtvHeapDesc;
	rtvHeapDesc.NumDescriptors = BUFFER_COUNT;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvHeapDesc.NodeMask = 0;
	m_RtvHeap = std::make_unique<DescriptorHeap>(pDevice, rtvHeapDesc);
	m_RtvDescriptorSize = pDevice->GetRenderTargetViewSize();
}

SwapChain::~SwapChain()
{
}

void SwapChain::Swap()
{
	m_SwapChain->Present(1, 0);
}

void SwapChain::ResetBuffers()
{
	for (int i = 0; i < BUFFER_COUNT; ++i)
		m_SwapChainBuffers[i].reset();

	m_CurrentBackBuffer = 0;
}

void SwapChain::ResetHeap(ID3D12Device* pDevice)
{
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(m_RtvHeap->GetCPUDescriptorHandle());
	for (UINT i = 0; i < BUFFER_COUNT; ++i)
	{
		//Get the ith buffer in the swapchain
		ThrowIfFailedSwapChain(m_SwapChain->GetBuffer(i, IID_PPV_ARGS(m_SwapChainBuffers[i]->GetResourceAddress())));

		//Create RTV to it
		pDevice->CreateRenderTargetView(m_SwapChainBuffers[i]->GetResource(), nullptr, rtvHeapHandle);

		//Next entry in heap
		rtvHeapHandle.Offset(1, m_RtvDescriptorSize);
	}

}

void SwapChain::ResizeBuffers(unsigned int width, unsigned int height)
{
	ThrowIfFailedSwapChain(m_SwapChain->ResizeBuffers(BUFFER_COUNT, width, height, m_Format, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));
}

IDXGISwapChain* SwapChain::GetSwapChain() const
{
	return m_SwapChain.Get();
}

IDXGISwapChain * const * SwapChain::GetSwapChainAddress() const
{
	return m_SwapChain.GetAddressOf();
}

unsigned int SwapChain::GetBufferCount() const
{
	return BUFFER_COUNT;
}
