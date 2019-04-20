#pragma once

class Adapter;

class Device
{
public:
	Device(Adapter* pAdapter);
	~Device();

	ID3D12Device* GetDevice() const;
	ID3D12Device* const* GetDeviceAddress() const;

	HRESULT CheckFeatureSupport(D3D12_FEATURE feature, void* featureSupportData, unsigned int size);

	UINT GetRenderTargetViewSize() const;
	UINT GetDepthStencilViewSize() const;
	UINT GetShaderResourceViewSize() const;

private:
	ComPtr<ID3D12Device> m_Device;
};