#pragma once

class Adapter;
class CommandAllocator;

#include "Buffer2D.h"
#include "DescriptorHeap.h"

class Device
{
public:
	Device(Adapter* pAdapter);
	~Device();

	ID3D12Device* GetDevice() const;
	ID3D12Device* const* GetDeviceAddress() const;

	void CreateCommandAllocator(const D3D12_COMMAND_LIST_TYPE& type, ID3D12CommandAllocator** ppCommandAllocator) const;
	void CreateCommandList(unsigned int nodeMask, const D3D12_COMMAND_LIST_TYPE& type, CommandAllocator* pAllocator, ID3D12GraphicsCommandList** ppCommandList) const;
	void CreateCommandQueue(const D3D12_COMMAND_QUEUE_DESC& desc, ID3D12CommandQueue** ppCommandQueue) const;
	void CreateFence(unsigned int initialValue, D3D12_FENCE_FLAGS flags, ID3D12Fence** ppFence) const;
	void CreateDescriptorHeap(const DescriptorHeapDesc& desc, ID3D12DescriptorHeap** ppDescriptorHeap) const;
	void CreateResource(const CoreResourceDesc& desc, ID3D12Resource** ppResource) const;
	void CreateRootSignature(unsigned int nodeMask, const void* pBlob, size_t blobSize, ID3D12RootSignature** ppRootSignature);

	void CreateRenderTargetView(Buffer2D *pBuffer, D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor, const D3D12_RENDER_TARGET_VIEW_DESC *pDesc = nullptr) const;
	void CreateDepthStencilView(Buffer2D* pBuffer, D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor, const D3D12_DEPTH_STENCIL_VIEW_DESC* pDesc = nullptr) const;

	HRESULT CheckFeatureSupport(D3D12_FEATURE feature, void* featureSupportData, unsigned int size);

	UINT GetRenderTargetViewSize() const;
	UINT GetDepthStencilViewSize() const;
	UINT GetShaderResourceViewSize() const;

private:
	ComPtr<ID3D12Device> m_Device;
};