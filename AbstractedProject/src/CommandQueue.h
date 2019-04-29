#pragma once

#include "Fence.h"

class Device;
class CommandList;

class CommandQueue
{
public:
	CommandQueue(Device* pDevice, const D3D12_COMMAND_QUEUE_DESC& desc);
	~CommandQueue();

	void Flush();

	ID3D12CommandQueue* GetCommandQueue() const;
	ID3D12CommandQueue* const* GetCommandQueueAddress() const;

	void ExecuteCommandList(CommandList* pCommandList) const;

private:
	ComPtr<ID3D12CommandQueue> m_CommandQueue;
	std::unique_ptr<Fence> m_Fence;
	unsigned int m_CurrentFenceValue;
};