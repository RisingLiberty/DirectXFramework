#pragma once

using ResourceDesc = D3D12_RESOURCE_DESC;

struct CoreResourceDesc
{
	CoreResourceDesc();

	D3D12_HEAP_PROPERTIES Props;
	D3D12_HEAP_FLAGS Flags;
	D3D12_RESOURCE_DESC Desc;
	D3D12_RESOURCE_STATES States;
	D3D12_CLEAR_VALUE ClearValue;
};

class Device;

class Buffer2D
{
public:
	Buffer2D(const ResourceDesc& desc);
	~Buffer2D();

	void Reset(Device* pDevice);

	ID3D12Resource* GetResource() const;
	ID3D12Resource* const* GetResourceAddress() const;
	ID3D12Resource** GetResourceAddress();

private:
	ResourceDesc m_Desc;
	ComPtr<ID3D12Resource> m_Resource;
};

using Texture = Buffer2D;
