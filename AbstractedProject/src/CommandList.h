#pragma once

class CommandAllocator;
class Device;

class CommandList
{
public:
	CommandList(Device* pDevice, const D3D12_COMMAND_LIST_TYPE& type, unsigned int nodeMask = 0);
	~CommandList();

	HRESULT Reset(ID3D12PipelineState* pInitialState = nullptr);
	HRESULT Close();

	ID3D12GraphicsCommandList* GetCommandList() const;
	ID3D12GraphicsCommandList* const* GetCommandListAddress() const;

private:
	ComPtr<ID3D12GraphicsCommandList> m_CommandList;
	std::unique_ptr<CommandAllocator> m_Allocator;
};