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
	// 업데이트때마다 현재 진동수(클럭 진동수) 받아옴
	QueryPerformanceCounter(&m_llCurCount);


	// cur - prev = 1프레임당 발생하는 진동수
	m_dDeltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart; // 고유진동수가 낮의면 몫이 커짐
	// DeltaTime : 한 프레임당 걸리는 시간 (컴퓨터가 느리면 델타타임이 더 큼)
	/*
	A Start            A               Goal
	B Start      B     *               Goal
	A 와 B는 1프레임에 저만큼 이동
	B가 *까지 가기 위해서 이동한만큼 한번 더 이동해야함
	즉 위치를 맞추려면 B는 1프레임동안 2번 움직여야 한다는 것
	위의 연산을 통해 b의 DT는 A의 두배가 나올것임 (이동 연산 차이가 2배가 나니까)
	이동할때마다 이동 수치에 fDT를 곱하게 되어
	B는 한번 update때마다 A의 2배만큼 움직여서
	1프레임에 도달했을때		A는 6번 update동안 10을 움직였다면
							B는 	3번 update동안 10을 움직이게 되는것
							A가 6번 update하는데 걸리는 시간과
							B가 3번 update하는데 걸리는 시간은 같다
	*/


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


	// 연산을 하고 나면 이전 진동수 설정
	m_llPrevCount = m_llCurCount; 

// 디버깅 모드일때만 실행 시키게 함 우리가 release로 하면 전처리기 자차에서 코드 사라짐

// 디버깅 모드에서 중단이 걸려서 Deltatime이 무한정 늘어난다
// 우리는 60프레임 기준 1프레임이 지났을때 1프레임만 지나게 할 것이다.
#ifdef _DEBUG
	if (m_dDeltaTime > (1. / 60.))
		m_dDeltaTime = (1. / 60.);
#endif

}






