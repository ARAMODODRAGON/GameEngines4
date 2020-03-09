#ifndef TIMER_H
#define TIMER_H

class Timer {
private:

	// time related variables
	unsigned int prevTicks, currentTicks;

public:
	// constructor and destructor
	Timer();
	~Timer() { }

	// member functions
	void Start();
	void UpdateGameTicks();
	float GetDeltaTimer() const;
	unsigned int GetSleepTime(const unsigned int fps_);
	float GetCurrentTicks();

public:
	// delete copy and move contructors/operators
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete;
};

#endif // !TIMER_H