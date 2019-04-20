#pragma once

#include "DisplayMode.h"

class Output
{
public:
	Output(IDXGIOutput* pOutput);
	~Output();

	void SetDefaultDisplayModes(DXGI_FORMAT format);

	IDXGIOutput* GetOutput() const;
	IDXGIOutput* const* GetOutputAddress() const;

	std::wstring GetDeviceName() const;
	std::vector<DisplayMode> GetDefaultDisplayModes() const;
private:
	unsigned int GetNrOfDisplays(DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM, unsigned int flags = 0) const;
	std::vector<DisplayMode> GetDisplayModes(DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM, unsigned int flags = 0);
private:
	ComPtr<IDXGIOutput> m_Output;
	std::wstring m_DeviceName;

	std::vector<DisplayMode> m_DisplayModes;
};