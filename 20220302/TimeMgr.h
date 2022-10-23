#pragma once
#include <chrono>

class CTimeMgr
{
	SINGLE(CTimeMgr);


private:




	LARGE_INTEGER	m_llCurCount;  // 부팅 후로부터 현재 cpu의 틱값 반환
	LARGE_INTEGER	m_llPrevCount; 
	LARGE_INTEGER	m_llFrequency; // cpu의 고유 진동수
	double			m_dDeltaTime;
	double			m_dAcc;
	UINT			m_iCallCount;
	UINT			m_iFPS;




	std::chrono::steady_clock::time_point	m_Current;
	std::chrono::steady_clock::time_point	m_Prev;

public:
	void init();
	void update();

public:
	double GetDT() const { return m_dDeltaTime; }
	float GetfDT() const { return static_cast<float>(m_dDeltaTime); }

	UINT GetCurCount() const { return static_cast<UINT>(m_llCurCount.QuadPart); }
};
