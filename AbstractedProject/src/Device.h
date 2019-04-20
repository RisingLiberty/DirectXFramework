#pragma once

class Device
{
public:
	Device(IDXGIAdapter* pAdapter);
	~Device();

	ID3D12Device* GetDevice() const;
	ID3D12Device* const* GetDeviceAddress() const;

	UINT GetRenderTargetViewSize() const;
	UINT GetDepthStencilViewSize() const;
	UINT GetShaderResourceViewSize() const;

private:
	ComPtr<ID3D12Device> m_Device;
};