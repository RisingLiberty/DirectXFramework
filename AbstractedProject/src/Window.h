#pragma once

#include "Event.h"

class Adapter;
class Output;

class Window
{
public:
	Window(unsigned int width, unsigned int height, const std::wstring& name, IDXGIFactory1* pFactory);
	~Window();

	UINT EventLoop();
	void Show();
	bool OnEvent(Event& e);

	bool IsPaused() const;
	const std::vector<std::unique_ptr<Adapter>>& GetAdapters() const;
	const std::vector<std::unique_ptr<Output>>& GetOutputs() const;

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	HWND GetHandle() const;

	void SetEventHandlerFn(const EventHandlerFn& callback);

private:
	static LRESULT CALLBACK WindowProcedureStatic(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT HandleEvent(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	HRESULT InitializeAdapters(IDXGIFactory1* pFactory);
	HRESULT InitializeOutputs();
	HRESULT InitializeDisplays();
	HRESULT InitializeWndClass();
	HRESULT Configure();

	bool OnResize(int width, int height);
	bool OnActivate();
	bool OnDeactivate();
private:
	HINSTANCE m_hInstance;
	HWND m_WindowHandle;
	unsigned int m_Width;
	unsigned int m_Height;
	std::wstring m_Name;
	WNDCLASS m_WndClass;
	bool m_IsPaused;

	std::vector<std::unique_ptr<Adapter>> m_Adapters;
	std::vector<std::unique_ptr<Output>> m_Outputs;

	EventHandlerFn m_EventHandlerFn;
	//std::vector<ComPtr<IDXGIOutput>> m_Outputs;
};