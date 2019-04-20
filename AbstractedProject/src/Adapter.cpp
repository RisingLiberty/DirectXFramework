#include "stdafx.h"
#include "Adapter.h"

Adapter::Adapter(IDXGIAdapter1* pAdapter)
{
	m_Adapter = pAdapter;
	DXGI_ADAPTER_DESC1 desc;
	pAdapter->GetDesc1(&desc);

	m_Description = desc.Description;
	m_VideoMemory = desc.DedicatedVideoMemory;
	m_SystemMemory = desc.DedicatedSystemMemory;
	m_Flags = desc.Flags;
}

Adapter::~Adapter()
{

}

IDXGIAdapter1* Adapter::GetAdapter() const
{
	return m_Adapter.Get();
}

IDXGIAdapter1* const * Adapter::GetAdapterAddress() const
{
	return m_Adapter.GetAddressOf();
}

std::wstring Adapter::GetDescription() const
{
	return m_Description;
}

size_t Adapter::GetVideoMemory() const
{
	return m_VideoMemory;
}

size_t Adapter::GetSystemMemory() const
{
	return m_SystemMemory;
}

unsigned int Adapter::GetFlags() const
{
	return m_Flags;
}