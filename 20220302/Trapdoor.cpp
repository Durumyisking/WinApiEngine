#include "pch.h"
#include "Trapdoor.h"

#include "ResMgr.h"
#include "Collider.h"
#include "Texture.h"

#include "Animation.h"

CTrapdoor::CTrapdoor()
	:m_pTex(nullptr)
	,m_vSlice()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"Trapdoor", L"texture\\Props\\door_11_trapdoor.bmp");

	SetName(L"Trapdoor");
	m_strAnimName = L"TrapdoorAppear";

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"TrapdoorAppear", m_pTex, Vec2(0.f, 64.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 3, false);
	GetAnimator()->CreateAnimation(L"TrapdoorDisappear", m_pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 3, false);
	GetAnimator()->CreateAnimation(L"TrapdoorIdle", m_pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 1, false);


	SetScale(Vec2(64.f, 64.f));

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(32.f, 32.f));

}

CTrapdoor::~CTrapdoor()
{
}

void CTrapdoor::update()
{
	if (L"TrapdoorAppear" == m_strAnimName && GetAnimator()->GetCurAnim()->IsFinish())
	{
		m_strAnimName = L"TrapdoorIdle";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(-42.f, -42.f), true);

	}

}

void CTrapdoor::render(HDC _dc)
{

		component_render(_dc);
}

void CTrapdoor::OnCollision(CCollider* _pOther)
{
}

void CTrapdoor::OnCollisionEnter(CCollider* _pOther)
{
}

void CTrapdoor::OnCollisionExit(CCollider* _pOther)
{
}

void CTrapdoor::Appear()
{
	m_strAnimName = L"TrapdoorAppear";
	PlayAnim(m_pAnim, m_strAnimName, Vec2(-42.f, -42.f), false);
}

void CTrapdoor::Disappear()
{
	m_strAnimName = L"TrapdoorDisappear";
	PlayAnim(m_pAnim, m_strAnimName, Vec2(-42.f, -42.f), false);
}
