#include "stdafx.h"
#include "Device.h"

#include "Adapter.h"

#include "CommandAllocator.h"

Device::Device(Adapter* pAdapter)
{
	ThrowIfFailedDefault(D3D12CreateDevice(pAdapter->GetAdapter(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(m_Device.ReleaseAndGetAddressOf())));
}

Device::~Device()
{

}

HRESULT Device::CheckFeatureSupport(D3D12_FEATURE feature, void* featureSupportData, unsigned int size)
{
	return m_Device->CheckFeatureSupport(feature, featureSupportData, size);
}

ID3D12Device* Device::GetDevice() const
{
	return m_Device.Get();
}

ID3D12Device* const* Device::GetDeviceAddress() const
{
	return m_Device.GetAddressOf();
}

void Device::CreateCommandAllocator(const D3D12_COMMAND_LIST_TYPE& type, ID3D12CommandAllocator** ppCommandAllocator) const
{
	ThrowIfFailedDevice(m_Device->CreateCommandAllocator(type, IID_PPV_ARGS(ppCommandAllocator)));
}

void Device::CreateCommandList(unsigned int nodeMask, const D3D12_COMMAND_LIST_TYPE& type, CommandAllocator* pAllocator, ID3D12GraphicsCommandList** ppCommandList) const
{
	ThrowIfFailedDevice(m_Device->CreateCommandList(nodeMask, type, pAllocator->GetAllocator(), nullptr, IID_PPV_ARGS(ppCommandList)));
}

void Device::CreateCommandQueue(const D3D12_COMMAND_QUEUE_DESC& desc, ID3D12CommandQueue** ppCommandQueue) const
{
	ThrowIfFailedDevice(m_Device->CreateCommandQueue(&desc, IID_PPV_ARGS(ppCommandQueue)));
}

void Device::CreateFence(unsigned int initialValue, D3D12_FENCE_FLAGS flags, ID3D12Fence** ppFence) const
{
	ThrowIfFailedDevice(m_Device->CreateFence(initialValue, flags, IID_PPV_ARGS(ppFence)));
}

void Device::CreateDescriptorHeap(const DescriptorHeapDesc& desc, ID3D12DescriptorHeap** ppDescriptorHeap) const
{
	ThrowIfFailedDevice(m_Device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(ppDescriptorHeap)));
}

void Device::CreateResource(const CoreResourceDesc& desc, ID3D12Resource** ppResource) const
{
	ThrowIfFailedDevice(m_Device->CreateCommittedResource(&desc.Props, desc.Flags, &desc.Desc, desc.States, &desc.ClearValue, IID_PPV_ARGS(ppResource)));
}

void Device::CreateDepthStencilView(ID3D12Resource* pResource, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor, const D3D12_DEPTH_STENCIL_VIEW_DESC* pDesc) const
{
	m_Device->CreateDepthStencilView(pResource, pDesc, DestDescriptor);
}

UINT Device::GetRenderTargetViewSize() const
{
	return m_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

}

UINT Device::GetDepthStencilViewSize() const
{
	return m_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
}

UINT Device::GetShaderResourceViewSize() const
{
	return m_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

