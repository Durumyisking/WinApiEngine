#include "pch.h"
#include "Core.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "CollisionMgr.h"
#include "EventMgr.h"
#include "UIMgr.h"
#include "Camera.h"

#include "Texture.h"
#include "ResMgr.h"

#include "Object.h"


CCore::CCore()
	: m_hWnd(0)
	, m_vResolution{}
	, m_hDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{

}

CCore::~CCore()
{	
	ReleaseDC(m_hWnd, m_hDC);
	


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


	// 이중 버퍼링 용도의 텍스처 생성
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_vResolution.x, (UINT)m_vResolution.y);



	// 브러시와 펜 생성
	CreateBrushPen();

	// 매니저 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CPathMgr::GetInst()->init();
	CCamera::GetInst()->init();
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
	CCamera::GetInst()->update();

	// Scene update
	CSceneMgr::GetInst()->update();

	// check collision
	CCollisionMgr::GetInst()->update();

	CUIMgr::GetInst()->update();
	
	// =========
	// Rendering
	// =========

	// 화면 클리어
	Rectangle(m_pMemTex->GetDC(), -1, -1, (int)m_vResolution.x + 1, (int)m_vResolution.y + 1);

	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());


	BitBlt(m_hDC, 0, 0, (int)m_vResolution.x, (int)m_vResolution.y,
		m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	// 이벤트 지연 처리
	CEventMgr::GetInst()->update();

	
	
}

void CCore::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
	m_arrBrush[(UINT)BRUSH_TYPE::WHITE] = (HBRUSH)GetStockObject(WHITE_BRUSH);

	// red green blue pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
