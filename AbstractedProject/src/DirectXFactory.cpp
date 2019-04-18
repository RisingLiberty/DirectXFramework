#include "stdafx.h"
#include "Utils.h"
#include "DirectXFactory.h"

DirectXFactory::DirectXFactory()
{
	ThrowIfFailedDefault(CreateDXGIFactory1(IID_PPV_ARGS(m_Factory.ReleaseAndGetAddressOf())));

}

DirectXFactory::~DirectXFactory()
{

}

IDXGIFactory1* DirectXFactory::GetFactory() const
{
	return m_Factory.Get();
}

IDXGIFactory1* const* DirectXFactory::GetFactoryAddress() const
{
	return m_Factory.GetAddressOf();
}
