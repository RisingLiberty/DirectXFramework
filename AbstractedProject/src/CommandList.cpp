#include "stdafx.h"
#include "CommandList.h"
#include "CommandAllocator.h"

#include "Device.h"
#include "Buffer2D.h"

CommandList::CommandList(Device* pDevice, const D3D12_COMMAND_LIST_TYPE & type, unsigned int nodeMask)
{
	m_Allocator = std::make_unique<CommandAllocator>(pDevice, type);

	pDevice->CreateCommandList(nodeMask, type, m_Allocator.get(), m_CommandList.ReleaseAndGetAddressOf());
}

CommandList::~CommandList()
{
}

void CommandList::Reset(ID3D12PipelineState* pInitialState)
{
	ThrowIfFailedCommandList(m_CommandList->Reset(m_Allocator->GetAllocator(), pInitialState));
}

void CommandList::Close()
{
	ThrowIfFailedCommandList(m_CommandList->Close());
}

ID3D12GraphicsCommandList * CommandList::GetCommandList() const
{
	return m_CommandList.Get();
}

ID3D12GraphicsCommandList* const* CommandList::GetCommandListAddress() const
{
	return m_CommandList.GetAddressOf();
}

void CommandList::TransitResourceToWrite(Buffer2D* pResource) const
{
	m_CommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pResource->GetResource(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));
}
