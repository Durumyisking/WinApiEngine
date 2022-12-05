#include "pch.h"
#include "Trite.h"

#include "Room.h"

CTrite::CTrite()
	: m_fAttackCooldown(0.f)
	, m_vJumpDest{}
	, m_vJumpDir{}
	, m_bDefinePos(false)

{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"TriteTex", L"texture\\Monster\\monster_082_trite.bmp");

	m_strAnimName = L"TRITE_IDLE";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"TRITE_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 0.1f, 1, false);
	GetAnimator()->CreateAnimation(L"TRITE_READY", m_pTex, Vec2(0.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 0.05f, 4, false);
	GetAnimator()->CreateAnimation(L"TRITE_AIR", m_pTex, Vec2(192.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 0.05f, 4, false);
	GetAnimator()->CreateAnimation(L"TRITE_LAND", m_pTex, Vec2(384.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 0.05f, 4, false);

	m_arrAnimName[static_cast<UINT>(MON_STATE::IDLE)] = L"TRITE_IDLE";
//	m_arrAnimName[static_cast<UINT>(MON_STATE::ATTACK)] = L"TRITE_ATTACK";

	PlayAnim(m_pAnim, m_strAnimName, Vec2(-24.f, -44.f), true);
}
CTrite::~CTrite()
{
}

void CTrite::update() 
{
	m_fAttackCooldown += fDT;




	if (2.3f < m_fAttackCooldown)
	{
		if (!m_bDefinePos)
		{
			void* p = new int();
			void* q = new int();
			srand((int)p);
			srand((int)q);

			int iToPlayer = rand() % 3;
			if (0 == iToPlayer)
			{
				m_vJumpDest = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetPos();
				GetRigidBody()->SetMaxVelocity(1500.f);
			}
			else
			{
				m_vJumpDest = Vec2(rand() % 901 - 450, rand() % 431 - 215);
				Vec2 vTemp = GetOwner()->GetPos();
				m_vJumpDest += vTemp;
				GetRigidBody()->SetMaxVelocity(500.f);
			}
			m_vJumpDir = m_vJumpDest - GetPos();
			m_vJumpDir.Normalize();

			delete p;
			delete q;

			m_bDefinePos = true;
		}
		if (m_bDefinePos)
		{
			m_bOnAir = true;
			GetRigidBody()->SetVelocity(m_vJumpDir  * 1500.f);
		}

	}

	CMonster::update();
}

void CTrite::Attack()
{
	if (2.1f < m_fAttackCooldown)
	{
		if (m_strAnimName == L"TRITE_IDLE")
		{
			GetAnimator()->ResetCurAnim();
			m_strAnimName = L"TRITE_READY";
			PlayAnim(m_pAnim, m_strAnimName, Vec2(-24.f, -44.f), false);
		}
	}
	if (m_strAnimName == L"TRITE_READY" && GetAnimator()->GetCurAnim()->IsFinish())
	{
		GetAnimator()->ResetCurAnim();
		m_strAnimName = L"TRITE_AIR";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(-24.f, -44.f), false);
	}
	if (m_strAnimName == L"TRITE_AIR" && GetAnimator()->GetCurAnim()->IsFinish())
	{
		GetAnimator()->ResetCurAnim();
		m_strAnimName = L"TRITE_LAND";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(-24.f, -44.f), false);
	}
	if (m_strAnimName == L"TRITE_LAND" && GetAnimator()->GetCurAnim()->IsFinish())
	{
		m_bOnAir = false;
		GetAnimator()->ResetCurAnim();
		m_strAnimName = L"TRITE_IDLE";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(-24.f, -44.f), true);
	}


	

	if (2.7f < m_fAttackCooldown)
	{
		GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));

		m_fAttackCooldown = 0.f;
		m_bDefinePos = false;
		m_vJumpDir = { 0.f ,0.f };
		m_vJumpDest = { 0.f ,0.f };

	}
}

void CTrite::OnCollision(CCollider* _pOther)
{
	CMonster::OnCollision(_pOther);
}

void CTrite::OnCollisionEnter(CCollider* _pOther)
{
	CMonster::OnCollisionEnter(_pOther);
}

void CTrite::OnCollisionExit(CCollider* _pOther)
{
	CMonster::OnCollisionExit(_pOther);
}
