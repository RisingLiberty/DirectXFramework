#pragma once

class Window
{
public:
	Window(int width, int height, const std::wstring& name, IDXGIFactory1* pFactory);
	~Window();

	void Show();

private:
	static LRESULT CALLBACK WindowProcdureStatic(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT HandleEvent(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	HRESULT InitializeAdapters(IDXGIFactory1* pFactory);
	HRESULT InitializeOutputs();
	HRESULT InitializeDisplays();
	HRESULT InitializeWndClass();
	HRESULT Configure();

private:
	HINSTANCE m_hInstance;
	HWND m_WindowHandle;
	int m_Width;
	int m_Height;
	std::wstring m_Name;
	WNDCLASS m_WndClass;

	std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter1>> m_Adapters;
	std::vector<Microsoft::WRL::ComPtr<IDXGIOutput>> m_Outputs;
};