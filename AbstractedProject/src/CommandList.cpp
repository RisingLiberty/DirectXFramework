#include "stdafx.h"
#include "CommandList.h"
#include "CommandAllocator.h"

#include "Device.h"

CommandList::CommandList(Device* pDevice, const D3D12_COMMAND_LIST_TYPE & type, unsigned int nodeMask)
{
	m_Allocator = std::make_unique<CommandAllocator>(pDevice, type);

	pDevice->CreateCommandList(nodeMask, type, m_Allocator.get(), m_CommandList.ReleaseAndGetAddressOf());
}

CommandList::~CommandList()
{
}

HRESULT CommandList::Reset(ID3D12PipelineState* pInitialState)
{
	return m_CommandList->Reset(m_Allocator->GetAllocator(), pInitialState);
}

HRESULT CommandList::Close()
{
	return m_CommandList->Close();
}

ID3D12GraphicsCommandList * CommandList::GetCommandList() const
{
	return m_CommandList.Get();
}

ID3D12GraphicsCommandList * const * CommandList::GetCommandListAddress() const
{
	return m_CommandList.GetAddressOf();
}
