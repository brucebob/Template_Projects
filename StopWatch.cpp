#include "StdAfx.h"
#include "StopWatch.h"


double StopWatch::LIToSecs( LARGE_INTEGER& L )
{
	return ((double)L.QuadPart / (double)frequency.QuadPart);
}

StopWatch::StopWatch()
{
	tracker.start.QuadPart = tracker.stop.QuadPart = 0;
	QueryPerformanceFrequency(&frequency);
}

void StopWatch::StartTimer()
{
	QueryPerformanceCounter(&tracker.start);
}

void StopWatch::EndTimer()
{
	QueryPerformanceCounter(&tracker.stop);
}

double StopWatch::ElapsedTime()
{
	if(tracker.stop.QuadPart != 0 && tracker.stop.QuadPart != 0)
	{
		LARGE_INTEGER time;
		time.QuadPart = tracker.stop.QuadPart - tracker.start.QuadPart;
		return LIToSecs(time);
	}
	else
	{
		throw "StopWatch start or end was not used"; 
	}
}
