#include "Timer.h"


CTimer::CTimer()
{
	// Query performance hardware 
	//trả về giá trị tần số của bộ đếm thời gian của hệ thống
	if (QueryPerformanceFrequency((LARGE_INTEGER *)&m_NS_Frequency))
	{
		// hardware supports
		m_IsPerfHardware = TRUE;
		//bắt đầu lấy về số xung nhịp của bộ đếm thời gian
		QueryPerformanceCounter((LARGE_INTEGER *)&m_NS_LastTime);
		//QueryPerformanceFrequency(&m_NS_LastTime);
		//QueryPerformanceCounter(&m_NS_CurrentTime);
	}

	else// no performance counter, read in using timeGetTime 
	{
		//hardware not supports
		m_IsPerfHardware = FALSE;
		m_MS_LastTime = timeGetTime();
		//m_MS_CurrentTime = timeGetTime();
	}
	m_LastFPSTime = timeGetTime();
	m_FPSAvarage = 0;
}


CTimer::~CTimer()
{

}

float CTimer::Tick()
{
	//static float deta_Time;
	float deta_Time;
	if (m_IsPerfHardware)
	{
		QueryPerformanceCounter(&m_NS_CurrentTime);

		deta_Time = (m_NS_CurrentTime.QuadPart - m_NS_LastTime.QuadPart) / float(m_NS_Frequency.QuadPart);
		int a = 10;
	}
	else
	{
		m_MS_CurrentTime = timeGetTime();
		deta_Time = (float)(m_MS_CurrentTime - m_MS_LastTime) / 1000.0f;
	}
	FreshTime();
	return deta_Time;

	
}


void CTimer::FreshTime()
{
	if (m_IsPerfHardware)
	{
		m_NS_LastTime = m_NS_CurrentTime;
	}
	else
	{
		m_MS_LastTime = m_MS_CurrentTime;
	}
}

float CTimer::GetFrameRate()
{
	return m_FPSAvarage;
}