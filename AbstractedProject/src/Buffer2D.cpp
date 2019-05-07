#include "stdafx.h"
#include "Buffer2D.h"

#include "Device.h"

CoreResourceDesc::CoreResourceDesc():
	Props(CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT)),
	Flags(D3D12_HEAP_FLAG_NONE),
	States(D3D12_RESOURCE_STATE_COMMON)
{

}

Buffer2D::Buffer2D() :
	m_Format(DXGI_FORMAT_UNKNOWN)
{

}

Buffer2D::Buffer2D(const DXGI_FORMAT& format):
	m_Format(format)
{

}

Buffer2D::~Buffer2D()
{

}

void Buffer2D::Unmap()
{
	m_Resource->Unmap(0, nullptr);
}

void Buffer2D::Reset()
{
	m_Resource.Reset();
}

void Buffer2D::Create(Device* pDevice, unsigned int newWidth, unsigned int newHeight, D3D12_RESOURCE_FLAGS flags)
{
	D3D12_RESOURCE_DESC desc;
	desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	desc.Alignment = 0;
	desc.Width = newWidth;
	desc.Height = newHeight;
	desc.DepthOrArraySize = 1;
	desc.MipLevels = 1;
	desc.Format = m_Format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	desc.Flags = flags;

	D3D12_CLEAR_VALUE optClear;
	optClear.Format = m_Format;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;

	CoreResourceDesc coreDesc;
	coreDesc.Desc = desc;
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

