#pragma once

struct Event
{
	Event();
	virtual ~Event();

	bool IsHandled;
};

typedef std::function<void(Event&)> EventHandlerFn;