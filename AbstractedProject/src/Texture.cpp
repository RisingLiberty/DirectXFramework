#include "stdafx.h"
#include "Texture.h"

#include "Device.h"

CoreResourceDesc::CoreResourceDesc():
	Props(CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT)),
	Flags(D3D12_HEAP_FLAG_NONE),
	States(D3D12_RESOURCE_STATE_COMMON)
{

}

Texture::Texture(const ResourceDesc& desc):
	m_Desc(desc)
{

}

Texture::~Texture()
{

}

void Texture::Reset(Device* pDevice)
{
	m_Resource.Reset();

	D3D12_RESOURCE_DESC depthStencilDesc;
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = m_Desc.Width;
	depthStencilDesc.Height = m_Desc.Height;
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.Format = m_Desc.Format;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE optClear;
	optClear.Format = m_Desc.Format;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;

	CoreResourceDesc coreDesc;
	coreDesc.Desc = depthStencilDesc;
	coreDesc.ClearValue = optClear;

	pDevice->CreateResource(coreDesc, m_Resource.ReleaseAndGetAddressOf());
}

ID3D12Resource* Texture::GetResource() const
{
	return m_Resource.Get();
}

ID3D12Resource* const* Texture::GetResourceAddress() const
{
	return m_Resource.GetAddressOf();
}

ID3D12Resource** Texture::GetResourceAddress()
{
	return m_Resource.GetAddressOf();
}

