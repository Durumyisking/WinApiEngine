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
	// ������Ʈ������ ���� ������(Ŭ�� ������) �޾ƿ�
	QueryPerformanceCounter(&m_llCurCount);


	// cur - prev = 1�����Ӵ� �߻��ϴ� ������
	m_dDeltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart; // ������������ ���Ǹ� ���� Ŀ��
	// DeltaTime : �� �����Ӵ� �ɸ��� �ð� (��ǻ�Ͱ� ������ ��ŸŸ���� �� ŭ)
	/*
	A Start            A               Goal
	B Start      B     *               Goal
	A �� B�� 1�����ӿ� ����ŭ �̵�
	B�� *���� ���� ���ؼ� �̵��Ѹ�ŭ �ѹ� �� �̵��ؾ���
	�� ��ġ�� ���߷��� B�� 1�����ӵ��� 2�� �������� �Ѵٴ� ��
	���� ������ ���� b�� DT�� A�� �ι谡 ���ð��� (�̵� ���� ���̰� 2�谡 ���ϱ�)
	�̵��Ҷ����� �̵� ��ġ�� fDT�� ���ϰ� �Ǿ�
	B�� �ѹ� update������ A�� 2�踸ŭ ��������
	1�����ӿ� ����������		A�� 6�� update���� 10�� �������ٸ�
							B�� 	3�� update���� 10�� �����̰� �Ǵ°�
							A�� 6�� update�ϴµ� �ɸ��� �ð���
							B�� 3�� update�ϴµ� �ɸ��� �ð��� ����
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


	// ������ �ϰ� ���� ���� ������ ����
	m_llPrevCount = m_llCurCount; 

// ����� ����϶��� ���� ��Ű�� �� �츮�� release�� �ϸ� ��ó���� �������� �ڵ� �����

// ����� ��忡�� �ߴ��� �ɷ��� Deltatime�� ������ �þ��
// �츮�� 60������ ���� 1�������� �������� 1�����Ӹ� ������ �� ���̴�.
#ifdef _DEBUG
	if (m_dDeltaTime > (1. / 60.))
		m_dDeltaTime = (1. / 60.);
#endif

}






