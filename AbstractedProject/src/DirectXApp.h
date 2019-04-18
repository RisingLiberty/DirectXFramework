#pragma once

#include "GameTimer.h"

class Window;
class DirectXFactory;

class DirectXApp
{
public:
	DirectXApp(HINSTANCE hInstance);
	~DirectXApp();

	HRESULT Start();

private:

	HRESULT Initialize();

	HRESULT MainLoop();

	void Update();
	void Draw();

private:
	std::wstring m_AppName;
	HINSTANCE m_hInstance;
	GameTimer m_GameTimer;
	std::unique_ptr<Window> m_Window;
	std::unique_ptr<DirectXFactory> m_Factory;
};