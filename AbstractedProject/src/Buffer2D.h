#pragma once

using ResourceDesc = D3D12_RESOURCE_DESC;

struct CoreResourceDesc
{
	CoreResourceDesc();

	D3D12_HEAP_PROPERTIES Props;
	D3D12_HEAP_FLAGS Flags;
	D3D12_RESOURCE_DESC Desc;
	D3D12_RESOURCE_STATES States;
	D3D12_CLEAR_VALUE* ClearValue;
};

class Device;

class Buffer2D
{
public:
	Buffer2D();
	Buffer2D(const DXGI_FORMAT& format);
	~Buffer2D();

	void Reset();
	void Create(Device* pDevice, unsigned int newWidth, unsigned int newHeight, D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE);
	void Unmap();
	
	DXGI_FORMAT m_Format;
	ID3D12Resource* GetResource() const;
	ID3D12Resource* const* GetResourceAddress() const;
	ID3D12Resource** GetResourceAddress();

private:
	ComPtr<ID3D12Resource> m_Resource;
};

using Texture = Buffer2D;
