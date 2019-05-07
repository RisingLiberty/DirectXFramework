#pragma once

class Device;

class CommandAllocator
{
public:
	CommandAllocator(Device* pDevice, const D3D12_COMMAND_LIST_TYPE& type = D3D12_COMMAND_LIST_TYPE_DIRECT);
	~CommandAllocator();

	ID3D12CommandAllocator* GetAllocator() const;
	ID3D12CommandAllocator* const* GetAllocatorAddress() const;

	void Reset();

private:
	ComPtr<ID3D12CommandAllocator> m_CommandAllocator;
};