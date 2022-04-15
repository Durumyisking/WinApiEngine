#include "pch.h"
#include "Core.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "CollisionMgr.h"
#include "EventMgr.h"
#include "Camera.h"

#include "Object.h"


CCore::CCore()
	: m_hWnd(0)
	, m_vResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{

}

CCore::~CCore()
{	
	ReleaseDC(m_hWnd, m_hDC);
	
	// compatible로 생성된 친구들은 delete로 삭제해야함
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
		DeleteObject(m_arrPen[i]);
}

// CObject g_obj;

int CCore::init(HWND _hWnd, Vec2 _vResolution)
{
	m_hWnd = _hWnd;
	m_vResolution = _vResolution;


	
	RECT rt = { 0.f, 0.f, m_vResolution.x, m_vResolution.y };
	
	
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); 
	SetWindowPos(_hWnd, nullptr, 0, 0,
		rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd); 

	// 이중 버퍼링 용도의 비트맵과 DC를 생성
	m_hBit = CreateCompatibleBitmap(m_hDC, (int)m_vResolution.x, (int)m_vResolution.y);
	// 이 가짜 비트맵에 완전 렌더링 한 후 그 결과를 진짜 비트맵에 올릴거임
	// 그래야 서로 다른 오브젝트들이 따로 렌더링되지 않음
	m_memDC = CreateCompatibleDC(m_hDC); // 화면에 직접 출력되지않는 memory dc 생성
	// DC가 버퍼링 용도의 비트맵을 사용하게함	
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);	// 어차피 기존 bitmap은 필요없음 새로운 비트맵으로 교체해버리면됨
							// 쓸때없는 메모리인 기존 비트맵 삭제

	// 브러시와 펜 생성
	CreateBrushPen();

	// 매니저 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CPathMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();
	CCollisionMgr::GetInst()->init();
	CEventMgr::GetInst()->init();


	return S_OK;
}


void CCore::progress()
{
	// Mgr update (1 frame cycle)
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	// CCamera::GetInst()->update();

	// Scene update
	CSceneMgr::GetInst()->update();

	// check collision
	CCollisionMgr::GetInst()->update();
	
	// =========
	// Rendering
	// =========

	// 화면 클리어
	Rectangle(m_memDC, -1, -1, (int)m_vResolution.x + 1, (int)m_vResolution.y + 1);


	CSceneMgr::GetInst()->render(m_memDC);

	// 비트블릿이라고 불러요
	BitBlt(m_hDC, 0, 0, (int)m_vResolution.x, (int)m_vResolution.y,
		m_memDC, 0, 0, SRCCOPY); // hdc에서 지정한 크기만큼 복사할 dc(memdc)의 지정한 위치에서 한픽셀씩 복사

	// 이벤트 지연 처리
	CEventMgr::GetInst()->update();

	
	
}

void CCore::CreateBrushPen()
{
	// GetStockObject에서 자주쑤는것들을 받아올수 있게 해줌
	// Window소속이라 우리가 delete 해 줄 필요 없음
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
	m_arrBrush[(UINT)BRUSH_TYPE::WHITE] = (HBRUSH)GetStockObject(WHITE_BRUSH);

	// red green blue pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
