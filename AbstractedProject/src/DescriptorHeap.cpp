#include "stdafx.h"
#include "DescriptorHeap.h"

#include "Device.h"

DescriptorHeap::DescriptorHeap(Device* pDevice, const DescriptorHeapDesc& desc)
{
	pDevice->CreateDescriptorHeap(desc, m_DescHeap.ReleaseAndGetAddressOf());
}

DescriptorHeap::~DescriptorHeap()
{

}

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::GetCPUDescriptorHandle() const
{
	return m_DescHeap->GetCPUDescriptorHandleForHeapStart();
}

ID3D12DescriptorHeap* DescriptorHeap::GetDescHeap() const
{
	return m_DescHeap.Get();
}

ID3D12DescriptorHeap* const* DescriptorHeap::GetDescHeapAddress() const
{
	return m_DescHeap.GetAddressOf();
}
