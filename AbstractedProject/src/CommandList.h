#pragma once

class CommandAllocator;
class Device;
class Buffer2D;

class CommandList
{
public:
	CommandList(Device* pDevice, const D3D12_COMMAND_LIST_TYPE& type, unsigned int nodeMask = 0);
	~CommandList();

	void Reset(ID3D12PipelineState* pInitialState = nullptr);
	void Close();

	ID3D12GraphicsCommandList* GetCommandList() const;
	ID3D12GraphicsCommandList* const* GetCommandListAddress() const;

	void TransitResourceToWrite(Buffer2D* pResource) const;

private:
	ComPtr<ID3D12GraphicsCommandList> m_CommandList;
	std::unique_ptr<CommandAllocator> m_Allocator;
};