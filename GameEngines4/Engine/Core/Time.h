#ifndef TIME_H
#define TIME_H
#include <ctime>

class Time {
private:
	std::clock_t startTime;
	double currentDuration, lastDuration;
	float delta;
public:

	// constructor & destructor
	Time() : currentDuration(0), lastDuration(0), delta(0), startTime(0) {
		// set startTime
		startTime = std::clock();
	}
	~Time() { }

	void UpdateTime() {
		// get the current duration since the program started
		currentDuration = (((double)std::clock()) - startTime) / (double)CLOCKS_PER_SEC;
		// calculate deltatime
		delta = (float)(currentDuration - lastDuration);
		// store currentduration for next frame
		lastDuration = currentDuration;
	}
	float GetDeltaFloat() { return delta; }
};

#endif // !TIME_H