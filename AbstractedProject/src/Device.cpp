#include "stdafx.h"
#include "Device.h"

#include "Utils.h"

Device::Device(IDXGIAdapter* pAdapter)
{
	ThrowIfFailedDefault(D3D12CreateDevice(pAdapter, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(m_Device.ReleaseAndGetAddressOf())));
}

Device::~Device()
{

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

