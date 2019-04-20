#pragma once

class CommandList
{
public:
	CommandList(ID3D12Device* pDevice, ID3D12CommandAllocator* pAllocator, const D3D12_COMMAND_LIST_TYPE& type, unsigned int nodeMask = 0);
	~CommandList();

	HRESULT Close();

	ID3D12GraphicsCommandList* GetCommandList() const;
	ID3D12GraphicsCommandList* const* GetCommandListAddress() const;

private:
	ComPtr<ID3D12GraphicsCommandList> m_CommandList;
};