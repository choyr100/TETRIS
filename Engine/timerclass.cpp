///////////////////////////////////////////////////////////////////////////////
// Filename: timerclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "timerclass.h"


TimerClass::TimerClass()
{
}


TimerClass::TimerClass(const TimerClass& other)
{
}


TimerClass::~TimerClass()
{
}


bool TimerClass::Initialize()
{
	m_TickPerSec = 0.f;
	m_LastElapsedTime = 0.f;
	LARGE_INTEGER frequency, startTime;
	// Check to see if this system supports high performance timers.
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	QueryPerformanceFrequency(&frequency);
	if(m_frequency == 0)
	{
		return false;
	}
	m_TickPerSec = frequency.QuadPart;
	// Find out how many times the frequency counter ticks every millisecond.
	m_ticksPerMs = (float)(m_frequency / 1000);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);
	QueryPerformanceCounter(&startTime);
	m_LastElapsedTime = startTime.QuadPart;
	return true;
}


void TimerClass::Frame()
{
	INT64 currentTime;
	float timeDifference;


	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	m_TimeDifference = (float)(currentTime - m_startTime);

	m_frameTime = m_TimeDifference / m_ticksPerMs;

	m_startTime = currentTime;

	return;
}

float TimerClass::GetElapsedTime()
{
	LARGE_INTEGER qwTime;
	QueryPerformanceCounter(&qwTime);
	float fElapsedTime = (float)((double)(qwTime.QuadPart - m_LastElapsedTime) / (double)m_TickPerSec);
	m_LastElapsedTime = qwTime.QuadPart;
	return fElapsedTime;
}


float TimerClass::GetTime()
{
	return m_frameTime;
}

float TimerClass::GetTimeDifference()
{
	return m_TimeDifference;
}