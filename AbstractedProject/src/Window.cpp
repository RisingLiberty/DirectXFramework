#include "stdafx.h"
#include "Window.h"
#include "Adapter.h"
#include "Output.h"

Window::Window(int width, int height, const std::wstring& name, IDXGIFactory1* pFactory) :
	m_Width(width),
	m_Height(height),
	m_Name(name),
	m_WndClass({}),
	m_IsPaused(false)
{
	this->InitializeAdapters(pFactory);
	this->InitializeOutputs();
	this->InitializeDisplays();
	this->InitializeWndClass();
	this->Configure();
}

Window::~Window()
{

}

UINT Window::EventLoop()
{
	MSG message = { 0 };

	while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);

		if (message.message == WM_QUIT)
			return message.message;
	}

	return message.message;
}

void Window::Show()
{
	ShowWindow(m_WindowHandle, SW_SHOWDEFAULT);
}

bool Window::IsPaused() const
{
	return m_IsPaused;
}

const std::vector<std::unique_ptr<Adapter>>& Window::GetAdapters() const
{
	return m_Adapters;
}

const std::vector<std::unique_ptr<Output>>& Window::GetOutputs() const
{
	return m_Outputs;
}

LRESULT Window::WindowProcdureStatic(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_CREATE)
	{
		CREATESTRUCT* pCs = reinterpret_cast<CREATESTRUCT*>(lParam);
		SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCs->lpCreateParams));
	}
	else
	{
		Window* pThis = reinterpret_cast<Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
		if (pThis)
			return pThis->HandleEvent(hwnd, message, wParam, lParam);
	}

	return DefWindowProcW(hwnd, message, wParam, lParam);
}

LRESULT Window::HandleEvent(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//Is sent when the window is being destroyed
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_ACTIVATE:
		if (wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE)
			m_IsPaused = false;
		else
			m_IsPaused = true;
		return 0;
	//case WM_RBUTTONDOWN:
	//	OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	//	return 0;
	//case WM_RBUTTONUP:
	//	OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	//	return 0;
	//case WM_MOUSEMOVE:
	//	OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

}

HRESULT Window::InitializeAdapters(IDXGIFactory1* pFactory)
{
	//enum adapters
	int adapterNr = 0;
	ComPtr<IDXGIAdapter1> pAdapter = nullptr;

	while (pFactory->EnumAdapters1(adapterNr++, pAdapter.GetAddressOf()) != DXGI_ERROR_NOT_FOUND)
		m_Adapters.emplace_back(std::make_unique<Adapter>(pAdapter.Get()));

	return S_OK;

}

HRESULT Window::InitializeOutputs()
{
	for (const std::unique_ptr<Adapter>& pAdapter : m_Adapters)
	{
		//enum outputs
		int outputNr = 0;
		ComPtr<IDXGIOutput> pTempOutput;

		while (pAdapter->GetAdapter()->EnumOutputs(outputNr++, pTempOutput.GetAddressOf()) != DXGI_ERROR_NOT_FOUND)
		{
			IDXGIOutput* pOutput;
			ThrowIfFailedDefault(pTempOutput->QueryInterface(IID_PPV_ARGS(&pOutput)));

			//std::wcout << L"Output: " << desc.DeviceName << L"\n";
			m_Outputs.emplace_back(std::make_unique<Output>(pOutput));
		}
	}

	return S_OK;
}

HRESULT Window::InitializeDisplays()
{
	for (const std::unique_ptr<Output>& pOutput : m_Outputs)
		pOutput->SetDefaultDisplayModes(DXGI_FORMAT_R8G8B8A8_UNORM);

	return S_OK;
}

HRESULT Window::InitializeWndClass()
{
	m_WndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_WndClass.hIcon = nullptr;
	m_WndClass.hbrBackground = nullptr;
	m_WndClass.style = CS_HREDRAW | CS_VREDRAW;
	m_WndClass.lpfnWndProc = WindowProcdureStatic;
	m_WndClass.hInstance = m_hInstance;
	m_WndClass.lpszClassName = m_Name.c_str();

	if (!RegisterClassW(&m_WndClass))
	{
		DWORD err = GetLastError();
		ThrowIfFailedWindow(HRESULT_FROM_WIN32(err));
	}

	return S_OK;
}

HRESULT Window::Configure()
{
	//Create window
	DXGI_OUTPUT_DESC outputDesc;
	ThrowIfFailedWindow(m_Outputs.front()->GetOutput()->GetDesc(&outputDesc));

	RECT r = { 0,0, m_Width, m_Height };
	AdjustWindowRect(&r, WS_OVERLAPPED, false);
	int winWidth = r.right - r.left;
	int winHeight = r.bottom - r.top;

	int x = outputDesc.DesktopCoordinates.left + ((outputDesc.DesktopCoordinates.right - outputDesc.DesktopCoordinates.left));
	int y = (int)((outputDesc.DesktopCoordinates.bottom - outputDesc.DesktopCoordinates.top) * 0.5f - winHeight * 0.5f);

	m_WindowHandle = CreateWindowExW(
		0L,
		m_Name.c_str(),
		m_Name.c_str(),
		WS_OVERLAPPED,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		winWidth,
		winHeight,
		NULL,			//no parent window
		nullptr,		//not using menus
		m_hInstance,
		this
	);

	if (!m_WindowHandle)
	{
		DWORD err = GetLastError();
		ThrowIfFailedWindow(HRESULT_FROM_WIN32(err));
	}

	this->Show();
	return S_OK;
}