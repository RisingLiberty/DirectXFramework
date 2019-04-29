#include "stdafx.h"
#include "Buffer2D.h"

#include "Device.h"

CoreResourceDesc::CoreResourceDesc():
	Props(CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT)),
	Flags(D3D12_HEAP_FLAG_NONE),
	States(D3D12_RESOURCE_STATE_COMMON)
{

}

Buffer2D::Buffer2D(const DXGI_FORMAT& format):
	m_Format(format)
{

}

Buffer2D::~Buffer2D()
{

}

void Buffer2D::Reset(Device* pDevice, unsigned int newWidth, unsigned int newHeight)
{
	m_Resource.Reset();

	D3D12_RESOURCE_DESC depthStencilDesc;
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = newWidth;
	depthStencilDesc.Height = newHeight;
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.Format = m_Format;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE optClear;
	optClear.Format = m_Format;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;

	CoreResourceDesc coreDesc;
	coreDesc.Desc = depthStencilDesc;
	coreDesc.ClearValue = &optClear;

	pDevice->CreateResource(coreDesc, m_Resource.ReleaseAndGetAddressOf());
}

ID3D12Resource* Buffer2D::GetResource() const
{
	return m_Resource.Get();
}

ID3D12Resource* const* Buffer2D::GetResourceAddress() const
{
	return m_Resource.GetAddressOf();
}

ID3D12Resource** Buffer2D::GetResourceAddress()
{
	return m_Resource.GetAddressOf();
}

