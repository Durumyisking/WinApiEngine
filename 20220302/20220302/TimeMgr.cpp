#include "pch.h"
#include "TimeMgr.h"
#include "Core.h"


CTimeMgr::CTimeMgr()
	: m_llCurCount{} 
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDeltaTime(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
{

}


CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	
	QueryPerformanceCounter(&m_llPrevCount);

	

	
	QueryPerformanceFrequency(&m_llFrequency);



}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);


	m_dDeltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	


	++m_iCallCount; 

	m_dAcc += m_dDeltaTime;

	
	
	
	if (m_dAcc >= 1.) 
	{
		m_iFPS = m_iCallCount;
		m_iCallCount = 0;
		m_dAcc = 0.;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %F", m_iFPS, m_dDeltaTime);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}



	m_llPrevCount = m_llCurCount; 

// 디버깅 모드일때만 실행 시키게 함 우리가 release로 하면 전처리기 자차에서 코드 사라짐

// 디버깅 모드에서 중단이 걸려서 Deltatimedl 무한정 늘어난다
// 우리는 60프레임 기준 1프레임이 지났을때 1프레임만 지나게 할 것이다.
#ifdef _DEBUG
	if (m_dDeltaTime > (1. / 60.))
		m_dDeltaTime = (1. / 60.);
#endif

}






