#include "Timer.h"
#include <SDL.h>

Timer::Timer()
	: prevTicks(0), currentTicks(0) { }

void Timer::Start() {
	// set ticks
	currentTicks = prevTicks = SDL_GetTicks();
}

void Timer::UpdateGameTicks() {
	prevTicks = currentTicks;
	currentTicks = SDL_GetTicks();
}

float Timer::GetDeltaTimer() const {
	return static_cast<float>(currentTicks - prevTicks) / 1000.0f;
}

unsigned int Timer::GetSleepTime(const unsigned int fps_) {
	unsigned int milliperframe = 1000 / fps_;
	if (milliperframe == 0) return 0;

	unsigned int sleepTime = milliperframe - SDL_GetTicks();
	if (sleepTime > milliperframe) return milliperframe;

	return sleepTime;
}

float Timer::GetCurrentTicks() {
	return static_cast<float>(currentTicks);
}
