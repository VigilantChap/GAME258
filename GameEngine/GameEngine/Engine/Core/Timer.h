#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
public:
	//Disabling ability to duplicate a Timer
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator =(const Timer&) = delete;
	Timer& operator =(Timer&&) = delete;

	Timer();


	void Start();
	void UpdateFrameTicks();
	float GetDeltaTime() const;
	unsigned int GetSleepTime(unsigned int fps_) const;
	float GetCurrentTicks();

private:
	unsigned int prevTicks, currentTicks;
	

};


#endif // !TIMER_H