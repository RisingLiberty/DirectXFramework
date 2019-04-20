#include "stdafx.h"
#include "CommandQueue.h"

CommandQueue::CommandQueue(ID3D12Device* pDevice, const D3D12_COMMAND_QUEUE_DESC& desc)
{
	ThrowIfFailedDevice(pDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(m_CommandQueue.ReleaseAndGetAddressOf())));
}

CommandQueue::~CommandQueue()
{
}

ID3D12CommandQueue * CommandQueue::GetCommandQueue() const
{
	return m_CommandQueue.Get();
}

ID3D12CommandQueue * const * CommandQueue::GetCommandQueueAddress() const
{
	return m_CommandQueue.GetAddressOf();
}
