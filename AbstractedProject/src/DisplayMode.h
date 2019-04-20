#pragma once

struct DisplayMode
{
	DisplayMode();
	DisplayMode(const DXGI_MODE_DESC& desc);
	~DisplayMode();

	unsigned int Width;
	unsigned int Height;
	float RefreshRate;
	DXGI_FORMAT Format;
	DXGI_MODE_SCANLINE_ORDER ScanlineOrder;
	DXGI_MODE_SCALING Scaling;
};