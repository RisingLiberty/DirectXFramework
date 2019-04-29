#include "stdafx.h"
#include "RootSignature.h"

#include "Device.h"

namespace
{
	ComPtr<ID3D10Blob> CreateSerializedRootSignature(const RootSignatureDesc& desc)
	{
		// Create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
		ComPtr<ID3DBlob> serializedRootSig = nullptr;
		ComPtr<ID3DBlob> errorBlob = nullptr;

		HRESULT hr = D3D12SerializeRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION_1,
			serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());

		if (errorBlob != nullptr)
			std::cout << (char*)errorBlob->GetBufferPointer();

		return serializedRootSig;
	}
}

RootSignature::RootSignature(Device* pDevice, RootParameter* pParameters, unsigned int nrOfParameters)
{
	// Create root CBV.
	for (unsigned int i = 0; i < nrOfParameters; ++i)
		pParameters[i].InitAsConstantBufferView(i);

	// A root signature is an array of root parameters.
	RootSignatureDesc rootSigDesc(nrOfParameters, pParameters, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	// Create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
	ComPtr<ID3DBlob> serializedRootSig = CreateSerializedRootSignature(rootSigDesc);
	pDevice->CreateRootSignature(0, serializedRootSig->GetBufferPointer(), serializedRootSig->GetBufferSize(), m_RootSignature.GetAddressOf());
}

ID3D12RootSignature* RootSignature::GetRootSignature() const
{
	return m_RootSignature.Get();
}

ID3D12RootSignature* const* RootSignature::GetRootSignatureAddress() const
{
	return m_RootSignature.GetAddressOf();
}