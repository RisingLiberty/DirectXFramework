#pragma once

class Window;
class DirectXFactory;
class CommandQueue;
class DescriptorHeap;
class Device;
class Buffer2D;

// For now the back buffer is as big as the window
class SwapChain
{
public:
	SwapChain(Device* pDevice, IDXGIFactory1* pFactory, ID3D12CommandQueue* pCommandQueue, Window* pWindow, int refreshRateNumerator, DXGI_FORMAT format);
	~SwapChain();

	void Swap();
	void Reset(Device* pDevice, unsigned int newWidth, unsigned int newHeight);
	void ResetBuffers();
	void ResetHeap(Device* pDevice);
	void ResizeBuffers(unsigned int width, unsigned int height);

	IDXGISwapChain* GetSwapChain() const;
	IDXGISwapChain* const* GetSwapChainAddress() const;
	unsigned int GetBufferCount() const;

private:
	DXGI_FORMAT m_Format;
	ComPtr<IDXGISwapChain> m_SwapChain;
	static const unsigned int BUFFER_COUNT = 2;
	std::array<std::unique_ptr<Buffer2D>, BUFFER_COUNT> m_SwapChainBuffers;
	unsigned int m_CurrentBackBuffer;
	std::unique_ptr<DescriptorHeap> m_RtvHeap;
	UINT m_RtvDescriptorSize;



};