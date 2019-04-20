#include "stdafx.h"
#include "DisplayMode.h"

DisplayMode::DisplayMode():
	Width(0),
	Height(0),
	RefreshRate(0),
	Format(DXGI_FORMAT_UNKNOWN),
	ScanlineOrder(DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED),
	Scaling(DXGI_MODE_SCALING_UNSPECIFIED)
{

}

DisplayMode::DisplayMode(const DXGI_MODE_DESC& desc):
	Width(desc.Width),
	Height(desc.Height),
	RefreshRate(desc.RefreshRate.Numerator / desc.RefreshRate.Denominator),
	Format(desc.Format),
	ScanlineOrder(desc.ScanlineOrdering),
	Scaling(desc.Scaling)
{

}

DisplayMode::~DisplayMode()
{

}