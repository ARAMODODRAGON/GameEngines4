#ifndef EVENT_EVENT_LISTENER_H
#define EVENT_EVENT_LISTENER_H

#include "MouseEventListener.h"

class EventListener {

	// disable copy & move constructors/operators
	EventListener(const EventListener&) = delete;
	EventListener(EventListener&&) = delete;
	EventListener& operator=(const EventListener&) = delete;
	EventListener& operator=(EventListener&&) = delete;

	EventListener() = delete;
	~EventListener();


public:

	static void Update();

};

#endif // !EVENT_EVENT_LISTENER_H