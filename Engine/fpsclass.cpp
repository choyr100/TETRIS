///////////////////////////////////////////////////////////////////////////////
// Filename: fpsclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "fpsclass.h"


FpsClass::FpsClass()
{
}


FpsClass::FpsClass(const FpsClass& other)
{
}


FpsClass::~FpsClass()
{
}


void FpsClass::Initialize()
{
	m_fps = 0;
	m_count = 0;
	m_time = 0;
	m_ftime = 0.f;
	m_startTime = timeGetTime();
	m_currentTime = m_startTime;
	return;
}


void FpsClass::Frame()
{
	m_count++;

	if(timeGetTime() >= (m_startTime + 1000))
	{
		m_fps = m_count;
		m_count = 0;
		m_time++;
		m_startTime = timeGetTime();
	}

	if (timeGetTime() >= (m_currentTime + 500))
	{
		m_ftime += 0.5f;
		m_currentTime = timeGetTime();
	}
}


int FpsClass::GetFps()
{
	return m_fps;
}

int FpsClass::GetTime()
{
	return m_time;
}

float FpsClass::GetFTime()
{
	return m_ftime;
}