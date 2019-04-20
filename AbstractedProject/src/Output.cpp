#include "stdafx.h"
#include "Output.h"

Output::Output(IDXGIOutput* pOutput)
{
	m_Output = pOutput;

	DXGI_OUTPUT_DESC desc;
	m_Output->GetDesc(&desc);

	m_DeviceName = desc.DeviceName;
}

Output::~Output()
{

}

void Output::SetDefaultDisplayModes(DXGI_FORMAT format)
{
	m_DisplayModes = this->GetDisplayModes(format);
}

IDXGIOutput* Output::GetOutput() const
{
	return m_Output.Get();
}

IDXGIOutput* const* Output::GetOutputAddress() const
{
	return m_Output.GetAddressOf();
}

std::wstring Output::GetDeviceName() const
{
	return m_DeviceName;
}

std::vector<DisplayMode> Output::GetDefaultDisplayModes() const
{
	return m_DisplayModes;
}

unsigned int Output::GetNrOfDisplays(DXGI_FORMAT format, unsigned int flags) const
{
	UINT count = 0;
	m_Output->GetDisplayModeList(format, flags, &count, nullptr);
	
	return count;
}

std::vector<DisplayMode> Output::GetDisplayModes(DXGI_FORMAT format, unsigned int flags)
{
	unsigned int nrOfDisplaysModes = this->GetNrOfDisplays();

	std::vector<DXGI_MODE_DESC> modes(nrOfDisplaysModes);
	m_Output->GetDisplayModeList(format, flags, &nrOfDisplaysModes, modes.data());


	std::vector<DisplayMode> displayModes(nrOfDisplaysModes);
	for (const DXGI_MODE_DESC& desc : modes)
		displayModes.emplace_back(DisplayMode(desc));

	return displayModes;
}