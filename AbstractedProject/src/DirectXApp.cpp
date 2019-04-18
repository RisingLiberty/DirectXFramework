#include "stdafx.h"
#include "DirectXApp.h"
#include "Window.h"
#include "DirectXFactory.h"
#include "Utils.h"

DirectXApp::DirectXApp(HINSTANCE hInstance):
	m_AppName(L"Direct X App"),
	m_hInstance(hInstance),
	m_Window(nullptr)
{

}

DirectXApp::~DirectXApp()
{

}

HRESULT DirectXApp::Start()
{
	ThrowIfFailedDefault(this->Initialize());

	this->MainLoop();

	return S_OK;
}

HRESULT DirectXApp::Initialize()
{
	m_Factory = std::make_unique<DirectXFactory>();
	m_Window = std::make_unique<Window>(1043, 720, m_AppName, m_Factory->GetFactory());


	return S_OK;
}

HRESULT DirectXApp::MainLoop()
{
	MSG msg = { 0 };

	m_GameTimer.Reset();

	while (msg.message != WM_QUIT)
	{
		//if there are window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{
			m_GameTimer.Tick();

			this->Update();
			this->Draw();

			//if (!m_IsPaused)
			//{
			//	this->CalculateFrameStats();
			//	this->Update(m_GameTimer.GetDeltaTime());
			//	this->Draw();
			//}
			//else
			//	Sleep(100);
		}
	}

	return (HRESULT)msg.wParam;
}

void DirectXApp::Update()
{

}

void DirectXApp::Draw()
{

}