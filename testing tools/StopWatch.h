#pragma once
#include <Windows.h>

class StopWatch
{
private:
	typedef struct
	{
		LARGE_INTEGER start;
		LARGE_INTEGER stop;
	}Timer;
	Timer tracker;
	LARGE_INTEGER frequency;

	double LIToSecs(LARGE_INTEGER& L);

public:
	StopWatch();
	void StartTimer();
	void EndTimer();
	double ElapsedTime();
};