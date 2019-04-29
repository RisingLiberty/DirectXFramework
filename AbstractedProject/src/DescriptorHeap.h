#pragma once

using DescriptorHeapDesc = D3D12_DESCRIPTOR_HEAP_DESC;

class Device;

class DescriptorHeap
{
public:
	DescriptorHeap(Device* pDevice, const DescriptorHeapDesc& desc);
	~DescriptorHeap();

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle() const;

	ID3D12DescriptorHeap* GetDescHeap() const;
	ID3D12DescriptorHeap* const* GetDescHeapAddress() const;

private:
	ComPtr<ID3D12DescriptorHeap> m_DescHeap;
};