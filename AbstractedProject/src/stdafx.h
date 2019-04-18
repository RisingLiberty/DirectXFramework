#pragma once

//Define to minimize the number of header files included in windows.h
#define WIN32_LEAN_AND_MEAN

//Basic windows methods
#include <Windows.h>
#include <windowsx.h>

//Contains the definition for the CommandLineToArgvW function
//This function wil be used later to parse the command-line arguments passed to the application
#include <shellapi.h> //For commandLineToArgvW

//Windows Runtime Library. Needed for Microsoft::WRL::Microsoft::WRL::ComPtr<> template class
//The Microsoft::WRL::ComPtr template class provides smart pointer functionality for COM objects.
#include <wrl.h>

//Windows extended methods
//#include <windowsx.h>
//#include <Xinput.h>

//DirectX 12
#include <d3d12.h>

//The Microsoft DirectX Graphics Infrastructure is used to manage the low level tasks
//such as enumerating GPU adapters, presenting the rendered image to the screen, and handling
//full-screen transitions, that are not necssarily part of the Direct X rendering API.
//DXGI 1.6 adds functionality in order to detect HDR displays.
//http://msdn.microsoft.com/en-us/library/windows/desktop/bb205075(v=vs.85).aspx
//http://msdn.microsoft.com/en-us/library/windows/desktop/ee417025(v=vs.85).aspx
//https://msdn.microsoft.com/en-us/library/windows/desktop/mt427784%28v=vs.85%29.aspx
#include <dxgi1_6.h>

//This contains functions to compile HLSL code at runtime.
//It is recommended to compile HLSL shaders at compile time but for demonstration purposes, 
//it might be more convenient to allow runtime compilation of HLSL shaders.
//https://blogs.msdn.microsoft.com/chuckw/2012/05/07/hlsl-fxc-and-d3dcompile/
#include <d3dcompiler.h>
#include <dxgidebug.h>

//DirectX math
//provides SIMD-friendly C++ types and functions for commonly used
//graphics related programming.
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

//D3D12 extension library
//This is not required to work with DirectX 12 but provides some useful classes that will
//simplify some of the functions that will be used throughout this tutorial.
//the d3dx12.h header is not included as part of the Windows 10 SDK and needs to be downloaded from here:
//https://github.com/Microsoft/DirectX-Graphics-Samples/tree/master/Libraries/D3DX12
#include <DirectX/d3dx12.h>

#include <initguid.h>
#include <array>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <unordered_map>

#include "Exceptions.h"

using Microsoft::WRL::ComPtr;