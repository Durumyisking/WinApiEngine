#include "pch.h"
#include "Charger.h"

#include "Scene.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Object.h"
#include "Collider.h"
#include "WallCollider.h"
#include "Missile.h"

CCharger::CCharger()
	: m_iAttackType(0)
	, m_bCharging(false)
	, m_fMoveTimer(0.f)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"ChargerTex", L"texture\\Monster\\monster_113_charger.bmp");
	m_strAnimName = L"Charger_IDLE_R";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Charger_IDLE_R", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 4, false);
	GetAnimator()->CreateAnimation(L"Charger_IDLE_L", m_pTex, Vec2(0.f, 32.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 4, false);
	GetAnimator()->CreateAnimation(L"Charger_IDLE_U", m_pTex, Vec2(0.f, 64.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 4, false);
	GetAnimator()->CreateAnimation(L"Charger_IDLE_D", m_pTex, Vec2(0.f, 96.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 4, false);

	GetAnimator()->CreateAnimation(L"Charger_ATTACK_R", m_pTex, Vec2(32.f, 128.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 1, false);
	GetAnimator()->CreateAnimation(L"Charger_ATTACK_L", m_pTex, Vec2(93.f, 128.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 1, false);
	GetAnimator()->CreateAnimation(L"Charger_ATTACK_U", m_pTex, Vec2(64.f, 128.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 1, false);
	GetAnimator()->CreateAnimation(L"Charger_ATTACK_D", m_pTex, Vec2(0.f, 128.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 1, false);

	m_arrAnimName[static_cast<UINT>(MON_STATE::IDLE)] = L"Charger_IDLE_R";
	m_arrAnimName[static_cast<UINT>(MON_STATE::ATTACK)] = L"Charger_ATTACK_R";
	m_vAnimOffset = Vec2(-20.f, -20.f);
	PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
	m_bDeadAnim = false;

}

CCharger::~CCharger()
{
}

// 한번 돌진하면 벽에 부딪힐때까지 해야함
// 돌진하면 m_bcharging = true
// 다음 update때 m_bcharging true면 계속 돌진해야함
// 벽에 oncollision인 상태에서 반대방향으로 돌진을 하게되면 movecheck에서 해당방향의 setvelocity가 0이기 때문에 벽에 부딪힐수 없어 무한 돌진함

void CCharger::update()
{
	CMonster::update();

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
				m_strAnimName = L"Charger_IDLE_U";
				break;
			case DIR::DOWN:
				m_strAnimName = L"Charger_IDLE_D";
				break;
			case DIR::RIGHT:
				m_strAnimName = L"Charger_IDLE_R";
				break;
			case DIR::LEFT:
				m_strAnimName = L"Charger_IDLE_L";
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
		if(AxisPlayerCheck())
			Attack();		
	}

}

void CCharger::Attack()
{
	
	if (!m_bCharging)
	{
		DIR eChargeDir = AxisCharge();
		switch (eChargeDir)
		{
		case DIR::UP:
			m_strAnimName = L"Charger_ATTACK_U";
			break;
		case DIR::DOWN:
			m_strAnimName = L"Charger_ATTACK_D";
			break;
		case DIR::RIGHT:
			m_strAnimName = L"Charger_ATTACK_R";
			break;
		case DIR::LEFT:
			m_strAnimName = L"Charger_ATTACK_L";
			break;
		case DIR::END:
			break;
		default:
			break;
		}
		PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);

		m_bCharging = true;
	}
}

void CCharger::OnCollision(CCollider* _pOther)
{
}

void CCharger::OnCollisionEnter(CCollider* _pOther)
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
		m_strAnimName = L"Charger_IDLE_R";
		PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
		if(m_bCharging)
			m_bCharging = false;
	}
	CMonster::OnCollisionEnter(_pOther);
}

void CCharger::OnCollisionExit(CCollider* _pOther)
{
	CMonster::OnCollisionExit(_pOther);
}
