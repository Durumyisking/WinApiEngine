#include "pch.h"
#include "MenuObj.h"

#include "ResMgr.h"
#include "KeyMgr.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"


CMenuObj::CMenuObj(const wstring & _animname)
	: pTitlemenuTex(nullptr)
	, pGamemenuTex(nullptr)
{
	m_strAnimName = _animname;

	pTitlemenuTex = CResMgr::GetInst()->LoadTexture(L"TitlemenuTex", L"texture\\UI\\titlemenuanim.bmp");
	pGamemenuTex = CResMgr::GetInst()->LoadTexture(L"GamemenuTex", L"texture\\UI\\gamemenudemoanim.bmp");
	CreateAnimator();
	
	GetAnimator()->CreateAnimation(L"titlemenu", pTitlemenuTex, Vec2(0.f, 110.f), Vec2(160.f, 158.f), Vec2(160.f, 0.f), 0.5f, 2, false);

	if (L"titlemenu" == m_strAnimName)
	{
		SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));
		PlayAnim(m_pAnim, m_strAnimName, Vec2(-185.f, -100.f));
	}
	if (L"title" == m_strAnimName)
	{
		SetPos(Vec2(100, 0));
	}
	if (L"gamemenu" == m_strAnimName)
	{
		SetPos(Vec2(500, 1150));
	}
}

CMenuObj::~CMenuObj()
{
}

void CMenuObj::update()
{


}

void CMenuObj::render(HDC _dc)	
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());;
	component_render(_dc);

	if (L"title" == m_strAnimName)
	{	
		TransparentBlt(_dc
			, static_cast<int>(vRenderPos.x), static_cast<int>(vRenderPos.y), 1120, 250
			, pTitlemenuTex->GetDC()
			, 0, 0, 480, 110
			, RGB(255, 0, 255));
	}

	if (L"gamemenu" == m_strAnimName)
	{
		TransparentBlt(_dc
			, static_cast<int>(vRenderPos.x), static_cast<int>(vRenderPos.y), 300, 100
			, pGamemenuTex->GetDC()
			, 32, 24, 115, 40
			, RGB(255, 0, 255));
	}
}

