#include "stdafx.h"
#include "CommandQueue.h"

#include "Device.h"
#include "CommandList.h"

CommandQueue::CommandQueue(Device* pDevice, const D3D12_COMMAND_QUEUE_DESC& desc):
	m_CurrentFenceValue(0)
{
	pDevice->CreateCommandQueue(desc, m_CommandQueue.ReleaseAndGetAddressOf());

	//After we have created our device, we can create our object for CPU/GPU synchronizatino.
	//In addtion, once we get to working with descriptors, we are going to need to know their size.
	//Descriptor sizes can vary across GPUs so we need to query this informatino. We cache the descriptor
	//sizes so that it is available when we need it for various descriptor types.
	m_Fence = std::make_unique<Fence>(pDevice, 0, D3D12_FENCE_FLAG_NONE);
}

CommandQueue::~CommandQueue()
{
}

void CommandQueue::Flush()
{
	// Advance the fence value to mark commands up to this fence point.
	m_CurrentFenceValue++;

	//Add an instruction to the command queue to set a new fence point.
	//Because we are on the GPU timeline, the new point won't be set until the GPU finishes
	//processing all the commands prior to this Signal().
	ThrowIfFailedCommandQueue(m_CommandQueue->Signal(m_Fence->GetFence(), m_CurrentFenceValue));

	if (m_Fence->GetValue() < m_CurrentFenceValue)
	{
		HANDLE eventHandle = CreateEventExA(nullptr, false, false, EVENT_ALL_ACCESS);
		assert(eventHandle); //Disables warning C6387

		//Fire event when GPU hits current fence.
		m_Fence->SetEventOnCompletion(m_CurrentFenceValue, eventHandle);

		//Wait till the GPU hits current fence event is fired.
		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}

}

void CommandQueue::ExecuteCommandLists(CommandList* pCommandList)
{
	ID3D12CommandList* pCmdList = pCommandList->GetCommandList();
	m_CommandQueue->ExecuteCommandLists(1, &pCmdList);
}

ID3D12CommandQueue * CommandQueue::GetCommandQueue() const
{
	return m_CommandQueue.Get();
}

ID3D12CommandQueue * const * CommandQueue::GetCommandQueueAddress() const
{
	return m_CommandQueue.GetAddressOf();
}

void CommandQueue::ExecuteCommandList(CommandList* pCommandList) const
{
	ID3D12CommandList* pCmdList = pCommandList->GetCommandList();
	m_CommandQueue->ExecuteCommandLists(1, &pCmdList);
}
