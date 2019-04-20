#pragma once

class CommandAllocator
{
public:
	CommandAllocator(ID3D12Device* pDevice, const D3D12_COMMAND_LIST_TYPE& type);
	~CommandAllocator();

	ID3D12CommandAllocator* GetAllocator() const;
	ID3D12CommandAllocator* const* GetAllocatorAddress() const;

private:
	ComPtr<ID3D12CommandAllocator> m_CommandAllocator;
};