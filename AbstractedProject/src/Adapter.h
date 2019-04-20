#pragma once

class Adapter
{
public:
	Adapter(IDXGIAdapter1* pAdapter);
	~Adapter();

	IDXGIAdapter1* GetAdapter() const;
	IDXGIAdapter1* const * GetAdapterAddress() const;

	std::wstring GetDescription() const;
	size_t GetVideoMemory() const;
	size_t GetSystemMemory() const;
	unsigned int GetFlags() const;

private:
	ComPtr<IDXGIAdapter1> m_Adapter;
	std::wstring m_Description;
	size_t m_VideoMemory;
	size_t m_SystemMemory;
	unsigned int m_Flags;
};