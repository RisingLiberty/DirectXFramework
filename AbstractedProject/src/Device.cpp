#include "stdafx.h"
#include "Device.h"

#include "Utils.h"

#include "Adapter.h"

Device::Device(Adapter* pAdapter)
{
	ThrowIfFailedDefault(D3D12CreateDevice(pAdapter->GetAdapter(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(m_Device.ReleaseAndGetAddressOf())));
}

Device::~Device()
{

}

HRESULT Device::CheckFeatureSupport(D3D12_FEATURE feature, void* featureSupportData, unsigned int size)
{
	return m_Device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, featureSupportData, size);
}

ID3D12Device* Device::GetDevice() const
{
	return m_Device.Get();
}

ID3D12Device* const* Device::GetDeviceAddress() const
{
	return m_Device.GetAddressOf();
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

