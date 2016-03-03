#pragma once

#include<windows.h>
#include<time.h>
class timer
{
private:
	LARGE_INTEGER beg, end, diff,freq,pStart;
	//float tElapsed;
	bool running;
public:
	timer();
	int ticTic(float tm=1000);
	void start();
	void reset();
	void stop();
	float elapsed();
	void pause();
	void resume();
};