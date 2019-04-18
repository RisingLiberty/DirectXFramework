#pragma once

class DirectXFactory
{
public:
	DirectXFactory();
	~DirectXFactory();

	IDXGIFactory1* GetFactory() const;
	IDXGIFactory1* const* GetFactoryAddress() const;

private:
	ComPtr<IDXGIFactory1> m_Factory;
};