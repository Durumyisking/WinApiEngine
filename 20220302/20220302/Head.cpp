#include "pch.h"
#include "Head.h"

#include "Collider.h"
#include "Animation.h"
#include "Animator.h"

#include "Missile.h"

#include "ResMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"


CHead::CHead()
	: m_pAnim(nullptr)
	, m_strAnimName(L"HEAD_DOWN")
{


	// 콜라이더 생성
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(HEAD_DEFAULT);
	SetScale(HEAD_DEFAULT);

	// 애니메이션 생성

	// isaac head
	CTexture* m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player\\isaac.bmp");

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"HEAD_UP", m_pTex, Vec2(170.f, 25.f), Vec2(28.f, 26.f), Vec2(40.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"HEAD_DOWN", m_pTex, Vec2(10.f, 25.f), Vec2(28.f, 26.f), Vec2(40.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"HEAD_LEFT", m_pTex, Vec2(250.f, 25.f), Vec2(28.f, 26.f), Vec2(40.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"HEAD_RIGHT", m_pTex, Vec2(90.f, 25.f), Vec2(28.f, 26.f), Vec2(40.f, 0.f), 0.5f, 2);


	PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f));


}


CHead::~CHead()
{
}


void CHead::update()
{

	CPlayer::update();

	// 문제점
	// 이동하면서 눈물쏠때 조건식 순서대로 우선순위가 작용함

	if (KEY_HOLD(KEY::W))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"HEAD_UP";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f));
	}
	if (KEY_HOLD(KEY::S))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"HEAD_DOWN";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f));
	}
	if (KEY_HOLD(KEY::A))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"HEAD_LEFT";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f));
	}
	if (KEY_HOLD(KEY::D))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"HEAD_RIGHT";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f));
	}



	if (KEY_HOLD(KEY::UP))
	{
		GetAnimator()->Play(m_strAnimName, false); 
		m_strAnimName = L"HEAD_UP";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f));

		CreateMissile(Vec2(0.f, -1.f));
	}
	if (KEY_HOLD(KEY::DOWN))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"HEAD_DOWN";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f));

		CreateMissile(Vec2(0.f, 1.f));
	}
	if (KEY_HOLD(KEY::LEFT))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"HEAD_LEFT";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f));

		CreateMissile(Vec2(-1.f, 0.f));
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"HEAD_RIGHT";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f));

		CreateMissile(Vec2(1.f, 0.f));
	}



	if (KEY_AWAY(KEY::UP) || KEY_AWAY(KEY::DOWN) ||
		KEY_AWAY(KEY::LEFT) || KEY_AWAY(KEY::RIGHT) ||
		KEY_AWAY(KEY::W) || KEY_AWAY(KEY::S) ||
		KEY_AWAY(KEY::A) || KEY_AWAY(KEY::D))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"HEAD_DOWN";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f));
	}
}

void CHead::CreateMissile(Vec2 _vDir)
{
	if (m_dPrevTime > m_fAttackDelay)
	{
		CMissile* pMissile = new CMissile;
		pMissile->SetDir(_vDir);
		pMissile->CreateMissile(MISSILE_TYPE::DEFAULT, GetPos() + Vec2(0.f, 0.f), GROUP_TYPE::PROJ_PLAYER);

		m_dPrevTime = 0.f;
	}

}
