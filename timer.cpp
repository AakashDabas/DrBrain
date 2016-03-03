#include"timer.h"

timer::timer()
{
	QueryPerformanceFrequency(&freq);
	running = false;
}

int timer::ticTic(float tm)
{
	if (!running)
		return -1;
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - beg.QuadPart;
	float tElapsed=((double)diff.QuadPart) / ((double)freq.QuadPart);
	tElapsed *= 1000;
	if (tElapsed>=tm)
	{
		running = false;
		return true;
	}
	else
		return false;
}

void timer::start()
{
	if (!running)
	{
		QueryPerformanceCounter(&beg);
		running = true;
	}
}

void timer::reset()
{
	running = true;
	QueryPerformanceCounter(&beg);
}

void timer::stop()
{
	running = false;
}

float timer::elapsed()
{
	if (!running)
		return -1; QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - beg.QuadPart;
	float tElapsed = ((double)diff.QuadPart) / ((double)freq.QuadPart);
	tElapsed *= 1000;
	return tElapsed;
}

void timer::pause()
{
	if (running)
	{
		QueryPerformanceCounter(&pStart);
	}
}

void timer::resume()
{
	if (running)

	{
		LARGE_INTEGER tmp;
		QueryPerformanceCounter(&tmp);
		beg.QuadPart = tmp.QuadPart - (pStart.QuadPart - beg.QuadPart);
	}
}