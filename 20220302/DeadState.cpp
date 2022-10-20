#include "pch.h"
#include "DeadState.h"
#include "Monster.h"
#include "Collider.h"
#include "RigidBody.h"


CDeadState::CDeadState()
	: CState(MON_STATE::DEAD)
	, m_fDeadAnimTimer(0.f)
	, m_bDead(false)
{
}

CDeadState::~CDeadState()
{
}

void CDeadState::Enter()
{
	CMonster* pMonster = GetMonster();
	// �����ִϸ��̼� ������ ���� �ִϸ��̼� ����
	if (L"" != pMonster->GetAnimName(MON_STATE::DEAD))
	{
		pMonster->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
		pMonster->SetCurrentAnim(pMonster->GetAnimName(MON_STATE::DEAD));
		pMonster->PlayAnim(pMonster->GetAnimInstance(), pMonster->GetCurrentAnim(), Vec2(0.f, 0.f), false);

		pMonster->GetCollider()->SwitchOff();
	}
	else
	{
		DeleteObject(pMonster);
		m_bDead = true;
	}
}

void CDeadState::Exit()
{
}

void CDeadState::update()
{
	if (!m_bDead)
	{
		m_fDeadAnimTimer += fDT;
		CMonster* pMonster = GetMonster();
		if (pMonster->GetDeadAnimTime() < m_fDeadAnimTimer)
		{
			DeleteObject(pMonster);
			m_bDead = true;
		}
	}
}
