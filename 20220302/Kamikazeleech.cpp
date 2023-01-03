#include "pch.h"
#include "Kamikazeleech.h"

#include "Scene.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Object.h"
#include "Collider.h"
#include "WallCollider.h"
#include "Missile.h"

CKamikazeleech::CKamikazeleech()
	: m_iAttackType(0)
	, m_bCharging(false)
	, m_fMoveTimer(0.f)
	, m_pEffectTex(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"KamikazeleechTex", L"texture\\Monster\\monster_174_kamikazeleech.bmp");
	m_pEffectTex = CResMgr::GetInst()->LoadTexture(L"Explode", L"texture\\Effect\\effect_029_explosion.bmp");
	// m_pEffectTex = CResMgr::GetInst()->FindTexture(L"Explode");
	m_strAnimName = L"Kamikazeleech_IDLE_R";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Kamikazeleech_IDLE_R", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 6, false);
	GetAnimator()->CreateAnimation(L"Kamikazeleech_IDLE_L", m_pTex, Vec2(0.f, 32.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 6, false);
	GetAnimator()->CreateAnimation(L"Kamikazeleech_IDLE_U", m_pTex, Vec2(0.f, 64.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 6, false);
	GetAnimator()->CreateAnimation(L"Kamikazeleech_IDLE_D", m_pTex, Vec2(0.f, 96.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 6, false);

	GetAnimator()->CreateAnimation(L"Kamikazeleech_DEATH", m_pEffectTex, Vec2(0.f, 0.f), Vec2(96.f, 96.f), Vec2(96.f, 0.f), 0.1f, 15, false);

	m_arrAnimName[static_cast<UINT>(MON_STATE::IDLE)] = L"Kamikazeleech_IDLE_R";
	m_arrAnimName[static_cast<UINT>(MON_STATE::DEAD)] = L"Kamikazeleech_DEATH";

	m_vAnimOffset = Vec2(-20.f, -20.f);
	PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);


}
CKamikazeleech::~CKamikazeleech()
{
}

void CKamikazeleech::update()
{
	if (GetOwner()->GetOwner()->GetCurrentRoom() == GetOwner())
	{
		if (m_Stat.m_iHP <= 0)
		{
			m_vAnimOffset = Vec2(-90.f, -130.f);
			GetCollider()->SetScale(Vec2(500.f, 500.f));
		}
		else
		{
			// 돌진중이 아닐때
			if (!m_bCharging)
			{
				m_fMoveTimer += fDT;

				// 이동 축이동만 합니다.
				if (m_fMoveTimer >= 0.5f)
				{
					m_fMoveTimer = 0.f;

					DIR eChargeDir = AxisPatrol();
					switch (eChargeDir)
					{
					case DIR::UP:
						m_strAnimName = L"Kamikazeleech_IDLE_U";
						break;
					case DIR::DOWN:
						m_strAnimName = L"Kamikazeleech_IDLE_D";
						break;
					case DIR::RIGHT:
						m_strAnimName = L"Kamikazeleech_IDLE_R";
						break;
					case DIR::LEFT:
						m_strAnimName = L"Kamikazeleech_IDLE_L";
						break;
					case DIR::END:
						m_fMoveTimer = 0.5f;
						break;
					default:
						break;
					}
					PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
				}
				// player의 위치 체크	
				if (AxisPlayerCheck())
					Attack();
			}
		}
		CMonster::update();
	}
}

void CKamikazeleech::Attack()
{
	if (GetOwner()->GetOwner()->GetCurrentRoom() == GetOwner())
	{

		if (!m_bCharging)
		{
			DIR eChargeDir = AxisCharge();
			switch (eChargeDir)
			{
			case DIR::UP:
				m_strAnimName = L"Kamikazeleech_IDLE_U";
				break;
			case DIR::DOWN:
				m_strAnimName = L"Kamikazeleech_IDLE_D";
				break;
			case DIR::RIGHT:
				m_strAnimName = L"Kamikazeleech_IDLE_R";
				break;
			case DIR::LEFT:
				m_strAnimName = L"Kamikazeleech_IDLE_L";
				break;
			case DIR::END:
				break;
			default:
				break;
			}
			GetAnimator()->FindAnimation(m_strAnimName)->SetDuration(0.05f);
			PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);

			m_bCharging = true;
		}
	}
}

void CKamikazeleech::OnCollision(CCollider* _pOther)
{
}

void CKamikazeleech::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Tear_Player" == pOtherObj->GetName())
	{
		CMissile* pMissileObj = dynamic_cast<CMissile*>(pOtherObj);
		m_Stat.m_iHP -= pMissileObj->GetDmg();
		return;
	}
	if (L"Wall" == pOtherObj->GetName())
	{
		GetAnimator()->FindAnimation(m_strAnimName)->SetDuration(0.1f);
		m_strAnimName = L"Kamikazeleech_IDLE_R";
		PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
		if (m_bCharging)
		{
			m_bCharging = false;
		}
	}

	if (L"Player" == pOtherObj->GetName())
	{
		GetStat().m_iHP = 0;
		m_vAnimOffset = Vec2(-90.f, -130.f);
		GetCollider()->SetScale(Vec2(300.f, 300.f));
	}

	CMonster::OnCollisionEnter(_pOther);
}

void CKamikazeleech::OnCollisionExit(CCollider* _pOther)
{
	CMonster::OnCollisionExit(_pOther);
}
