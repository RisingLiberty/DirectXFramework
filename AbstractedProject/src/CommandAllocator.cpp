#include "stdafx.h"
#include "CommandAllocator.h"

#include "Device.h"

CommandAllocator::CommandAllocator(Device* pDevice, const D3D12_COMMAND_LIST_TYPE& type)
{
	pDevice->CreateCommandAllocator(type, m_CommandAllocator.ReleaseAndGetAddressOf());
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

void CommandAllocator::Reset()
{
	ThrowIfFailedCommandAllocator(m_CommandAllocator->Reset());
}