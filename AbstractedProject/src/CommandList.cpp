#include "stdafx.h"
#include "CommandList.h"

CommandList::CommandList(ID3D12Device* pDevice, ID3D12CommandAllocator* pAllocator, const D3D12_COMMAND_LIST_TYPE & type, unsigned int nodeMask)
{
	ThrowIfFailedDevice(pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, pAllocator, nullptr, IID_PPV_ARGS(m_CommandList.ReleaseAndGetAddressOf())));
}

CommandList::~CommandList()
{
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
