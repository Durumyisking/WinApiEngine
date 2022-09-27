#include "pch.h"
#include "UI.h"

#include "Core.h"

#include "Camera.h"
#include "KeyMgr.h"
#include "Texture.h"

#include "SelectGDI.h"

// 모든 UI의 부모로써 추상 클래스로 객체 생성 못하게 할거임
// UI들은 부모 자식관계를 가짐
// Scene에는 가장 최상위 부모 단 하나만 넣어줄 것임



CUI::CUI(bool _bCamAff)
	: m_pParentUI(nullptr)
	, m_bCameAffected(_bCamAff)
	, m_bMouseOn(false)
	, m_pTex(nullptr)
	, m_vSlice(Vec2(0, 0))
{
}
CUI::CUI(const CUI& _origin)
	: CObject(_origin)
	, m_pParentUI(nullptr)
	, m_bCameAffected(false)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
	, m_pTex(nullptr)
	, m_vSlice(Vec2(0, 0))
{
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
		AddChild(_origin.m_vecChildUI[i]->Clone());
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}

void CUI::update()
{
	update_child();
}

// 최종 위치를 설정해줌
void CUI::finalupdate()
{
	CObject::finalupdate();

	m_vFinalPos = GetPos();

	// UI의 최종 좌표를 구한다.
	if (GetParent())
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}
	MouseOnCheck();

	//if (KEY_AWAY(KEY::LBTN))
	//	m_bMouseOn = false;

	finalupdate_child();

}

void CUI::render(HDC _dc)
{
	// 그냥 getpos라고 하면 vParnetpos가 더해지지 않은 초기화 위치로 설정됨
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();


	if (m_bCameAffected)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}


	if (nullptr != m_pTex)
	{

		int iWidth = (int)m_pTex->GetWidth();
		int iHeight = (int)m_pTex->GetHeight();

		TransparentBlt(_dc
			, static_cast<int>(vPos.x), static_cast<int>(vPos.y)
			, static_cast<int>(vScale.x) * 2, static_cast<int>(vScale.y) * 2
			, m_pTex->GetDC()
			, static_cast<int>(GetScale().x * m_vSlice.x)
			, static_cast<int>(GetScale().y * m_vSlice.y)
			, static_cast<int>(vScale.x) , static_cast<int>(vScale.y)
			, RGB(255, 0, 255));



	}
	else if (m_bLbtnDown)
	{
		CSelectGDI select(_dc, PEN_TYPE::RED);

		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));
	}
	else
	{
		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));
	}

	render_child(_dc);
}

void CUI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finalupdate();
	}

}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::MouseOn()
{
}

void CUI::MouseLbtnDown()
{
}

void CUI::MouseLbtnUp()
{

}

void CUI::MouseLbtnClicked()
{

}

void CUI::MouseOnCheck()
{

	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();



	if (m_bCameAffected)
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}
	
	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}

	wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"MXY : %f, %f		on : %d", vMousePos.x, vMousePos.y, m_bMouseOn);
	SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);


}

