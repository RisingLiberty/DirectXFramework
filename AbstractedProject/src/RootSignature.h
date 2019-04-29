#pragma once

using RootParameter = CD3DX12_ROOT_PARAMETER;
using RootSignatureDesc = CD3DX12_ROOT_SIGNATURE_DESC;

class Device;

class RootSignature
{
public:
	RootSignature(Device* pDevice, RootParameter* pParameters, unsigned int nrOfParameters);

	ID3D12RootSignature* GetRootSignature() const;
	ID3D12RootSignature* const* GetRootSignatureAddress() const;

private:
	ComPtr<ID3D12RootSignature> m_RootSignature;

};