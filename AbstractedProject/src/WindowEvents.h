#pragma once

#include "Event.h"

enum class WindowEventType
{
	UNDEFINED,

	RESIZE,
	KEY_UP,
	KEY_DOWN,
	ACTIVATE,
	DESTROY,
	MOUSE_DOWN,
	MOUSE_UP,
	MOUSE_MOVE
};

struct WindowEvent : public Event
{
	WindowEvent();
	virtual ~WindowEvent();

	virtual WindowEventType GetType() const;
};

struct WindowResizeEvent : public WindowEvent
{
	WindowResizeEvent(int newWidth, int newHeight);
	
	virtual WindowEventType GetType() const;

	int Width;
	int Height;
};

struct WindowKeyUpEvent : public WindowEvent
{
	WindowKeyUpEvent(unsigned int keycode);
	virtual WindowEventType GetType() const;

	unsigned int KeyCode;
};

struct WindowKeyDownEvent : public WindowEvent
{
	WindowKeyDownEvent(unsigned int keycode);
	virtual WindowEventType GetType() const;

	unsigned int KeyCode;
};

struct WindowActivateEvent : public WindowEvent
{
	WindowActivateEvent(bool isActive);
	virtual WindowEventType GetType() const;

	bool IsActive;
};

struct WindowDestroyEvent : public WindowEvent
{
	virtual WindowEventType GetType() const;

};

struct WindowMouseDownEvent : public WindowEvent
{
	WindowMouseDownEvent(unsigned char mouseCode);
	virtual WindowEventType GetType() const;

	unsigned char MouseCode;
};

struct WindowMouseUpEvent : public WindowEvent
{
	WindowMouseUpEvent(unsigned char mouseCode);
	virtual WindowEventType GetType() const;

	unsigned char MouseCode;
};

struct WindowMouseMoveEvent : public WindowEvent
{
	WindowMouseMoveEvent(unsigned int x, unsigned int y);
	virtual WindowEventType GetType() const;

	unsigned int X;
	unsigned int Y;
};
