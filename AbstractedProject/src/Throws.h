#pragma once

inline std::wstring AnsiToWString(const std::string& str)
{
	WCHAR buffer[512];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer, 512);
	return std::wstring(buffer);
}

#ifndef ThrowIfFailed
#define ThrowIfFailed(x, exception)\
{\
    HRESULT _hr_ = (x);\
    if(FAILED(_hr_)) { throw exception(_hr_, L#x, AnsiToWString(__FILE__), __LINE__); } \
}

#define ThrowIfFailedDefault(x)\
{\
    HRESULT _hr_ = (x);\
    if(FAILED(_hr_)) { ThrowIfFailed(x, Exception); } \
}

#define ThrowIfFailedWindow(x)\
{\
    HRESULT _hr_ = (x);\
    if(FAILED(_hr_)) { ThrowIfFailed(x, WindowException); } \
}

#define ThrowIfFailedDevice(x)\
{\
    HRESULT _hr_ = (x);\
    if(FAILED(_hr_)) { ThrowIfFailed(x, DeviceException); } \
}

#endif
