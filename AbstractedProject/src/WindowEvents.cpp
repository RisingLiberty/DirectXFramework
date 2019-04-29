#include "stdafx.h"
#include "WindowEvents.h"

WindowEvent::WindowEvent()
{
}

WindowEvent::~WindowEvent()
{
}

WindowEventType WindowEvent::GetType() const
{
	return WindowEventType::UNDEFINED;
}

WindowResizeEvent::WindowResizeEvent(int newWidth, int newHeight):
	Width(newWidth),
	Height(newHeight)
{
}

WindowEventType WindowResizeEvent::GetType() const
{
	return WindowEventType::RESIZE;
}

WindowKeyUpEvent::WindowKeyUpEvent(unsigned int keycode):
	KeyCode(keycode)
{
}

WindowEventType WindowKeyUpEvent::GetType() const
{
	return WindowEventType::KEY_UP;
}

WindowKeyDownEvent::WindowKeyDownEvent(unsigned int keycode):
	KeyCode(keycode)
{
}

WindowEventType WindowKeyDownEvent::GetType() const
{
	return WindowEventType::KEY_DOWN;
}

WindowMouseMoveEvent::WindowMouseMoveEvent(unsigned int x, unsigned int y):
	X(x),
	Y(y)
{
}

WindowEventType WindowMouseMoveEvent::GetType() const
{
	return WindowEventType::MOUSE_MOVE;
}

WindowMouseDownEvent::WindowMouseDownEvent(unsigned char mouseCode):
	MouseCode(mouseCode)
{
}

WindowEventType WindowMouseDownEvent::GetType() const
{
	return WindowEventType::MOUSE_DOWN;
}

WindowMouseUpEvent::WindowMouseUpEvent(unsigned char mouseCode) :
	MouseCode(mouseCode)
{
}

WindowEventType WindowMouseUpEvent::GetType() const
{
	return WindowEventType::MOUSE_UP;
}

WindowActivateEvent::WindowActivateEvent(bool isActive):
	IsActive(isActive)
{
}

WindowEventType WindowActivateEvent::GetType() const
{
	return WindowEventType::ACTIVATE;
}

WindowEventType WindowDestroyEvent::GetType() const
{
	return WindowEventType::DESTROY;
}