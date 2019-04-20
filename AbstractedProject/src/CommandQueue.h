#pragma once

class CommandQueue
{
public:
	CommandQueue(ID3D12Device* pDevice, const D3D12_COMMAND_QUEUE_DESC& desc);
	~CommandQueue();

	ID3D12CommandQueue* GetCommandQueue() const;
	ID3D12CommandQueue* const* GetCommandQueueAddress() const;

private:
	ComPtr<ID3D12CommandQueue> m_CommandQueue;
};