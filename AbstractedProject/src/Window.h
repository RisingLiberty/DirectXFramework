#pragma once

class Window
{
public:
	Window(int width, int height, const std::wstring& name, IDXGIFactory1* pFactory);
	~Window();

	UINT EventLoop();
	void Show();

	bool IsPaused() const;
	const std::vector<ComPtr<IDXGIAdapter1>>& GetAdapters() const;
	const std::vector<ComPtr<IDXGIOutput>>& GetOutputs() const;

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
	bool m_IsPaused;

	std::vector<ComPtr<IDXGIAdapter1>> m_Adapters;
	std::vector<ComPtr<IDXGIOutput>> m_Outputs;
};