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
{
	SetScale(Vec2(84.f, 75.f));


	// 애니메이션 생성

	// isaac head
	m_strAnimName = L"HEAD_IDLE";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"HEAD_IDLE", m_pTex, Vec2(10.f, 25.f), Vec2(28.f, 26.f), Vec2(40.f, 0.f), 0.5f, 1, false);


	GetAnimator()->CreateAnimation(L"HEAD_UP", m_pTex, Vec2(170.f, 25.f), Vec2(28.f, 26.f), Vec2(40.f, 0.f), 0.5f, 2, false);
	GetAnimator()->CreateAnimation(L"HEAD_DOWN", m_pTex, Vec2(10.f, 25.f), Vec2(28.f, 26.f), Vec2(40.f, 0.f), 0.5f, 2, false);
	GetAnimator()->CreateAnimation(L"HEAD_LEFT", m_pTex, Vec2(250.f, 25.f), Vec2(28.f, 26.f), Vec2(40.f, 0.f), 0.5f, 2, false);
	GetAnimator()->CreateAnimation(L"HEAD_RIGHT", m_pTex, Vec2(90.f, 25.f), Vec2(28.f, 26.f), Vec2(40.f, 0.f), 0.5f, 2, false);


	PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);


}


CHead::~CHead()
{
}



void CHead::update()
{

	CPlayer::update();

	if (m_finvincibilityTime > 0.5f)
	{
		m_strAnimName = L"HEAD_IDLE";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);
	}

	// 문제점
	// 이동하면서 눈물쏠때 조건식 순서대로 우선순위가 작용함

	if (KEY_HOLD(KEY::W))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"HEAD_UP";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);
	}
	if (KEY_HOLD(KEY::S))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"HEAD_DOWN";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);
	}
	if (KEY_HOLD(KEY::A))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"HEAD_LEFT";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);
	}
	if (KEY_HOLD(KEY::D))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"HEAD_RIGHT";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);
	}



	if (KEY_HOLD(KEY::UP))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"HEAD_UP";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);

		CreateMissile(Vec2(0.f, -1.f));
	}
	if (KEY_HOLD(KEY::DOWN))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"HEAD_DOWN";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);

		CreateMissile(Vec2(0.f, 1.f));
	}
	if (KEY_HOLD(KEY::LEFT))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"HEAD_LEFT";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);

		CreateMissile(Vec2(-1.f, 0.f));
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"HEAD_RIGHT";	
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);

		CreateMissile(Vec2(1.f, 0.f));
	}



	if (KEY_AWAY(KEY::UP) || KEY_AWAY(KEY::DOWN) ||
		KEY_AWAY(KEY::LEFT) || KEY_AWAY(KEY::RIGHT) ||
		KEY_AWAY(KEY::W) || KEY_AWAY(KEY::S) ||
		KEY_AWAY(KEY::A) || KEY_AWAY(KEY::D))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"HEAD_IDLE";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);
	}
}



void CHead::OnCollision(CCollider * _pOther)
{

	CObject* pOtherObj = _pOther->GetObj();

	// monster
	if (L"Monster" == pOtherObj->GetName())
	{
		GetAnimator()->Play(m_strAnimName, false);
	}

}

void CHead::OnCollisionEnter(CCollider * _pOther)
{
}

void CHead::OnCollisionExit(CCollider * _pOther)
{
}

void CHead::CreateMissile(Vec2 _vDir)
{
	if (m_dAttackDealy > m_pStat->m_fRate)
	{
		if (m_pOwner->m_vInventory[static_cast<UINT>(ITEM_TABLE::innereye)] > 0)
		{
			for (int  i = -1; i < 2; i++)
			{
				CMissile* pMissile = new CMissile(m_pStat->m_fShotSpeed, m_pStat->m_iDmg);
				pMissile->SetDir(_vDir.Rotate(5 * i));
				pMissile->CreateMissile(MISSILE_TYPE::DEFAULT, GROUP_TYPE::PROJ_PLAYER, this);
			}
		}
		else
		{
			CMissile* pMissile = new CMissile(m_pStat->m_fShotSpeed, m_pStat->m_iDmg);
			pMissile->SetDir(_vDir);
			pMissile->CreateMissile(MISSILE_TYPE::DEFAULT, GROUP_TYPE::PROJ_PLAYER, this);
		}
		m_dAttackDealy = 0.f;
	}

}
