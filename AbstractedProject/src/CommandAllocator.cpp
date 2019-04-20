#include "stdafx.h"
#include "CommandAllocator.h"

CommandAllocator::CommandAllocator(ID3D12Device * pDevice, const D3D12_COMMAND_LIST_TYPE & type)
{
	ThrowIfFailedDevice(pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_CommandAllocator.ReleaseAndGetAddressOf())));
}

CommandAllocator::~CommandAllocator()
{
}

ID3D12CommandAllocator * CommandAllocator::GetAllocator() const
{
	return m_CommandAllocator.Get();
}

ID3D12CommandAllocator * const * CommandAllocator::GetAllocatorAddress() const
{
	return m_CommandAllocator.GetAddressOf();
}
