#include "pch.h"
#include "DeadState.h"
#include "Monster.h"
#include "Collider.h"
#include "RigidBody.h"


CDeadState::CDeadState()
	: CState(MON_STATE::DEAD)
	, m_fDeadAnimTimer(0.f)
{
}

CDeadState::~CDeadState()
{
}

void CDeadState::Enter()
{
	CMonster* pMonster = GetMonster();
	// 죽음애니메이션 있으면 죽음 애니메이션 실행
	if (L"" != pMonster->GetAnimName(MON_STATE::DEAD))
	{
		pMonster->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
		pMonster->SetCurrentAnim(pMonster->GetAnimName(MON_STATE::DEAD));
		pMonster->PlayAnim(pMonster->GetAnimInstance(), pMonster->GetCurrentAnim(), Vec2(0.f, 0.f), false);
		for (size_t i = 0; i < pMonster->GetColliderVector().size(); i++)
		{
			pMonster->GetColliderVector()[i]->SwitchOff();
		}
	}
	else
	{
		DeleteObject(pMonster);
	}
}

void CDeadState::Exit()
{
}

void CDeadState::update()
{
	m_fDeadAnimTimer += fDT;
	CMonster* pMonster = GetMonster();
	if (pMonster->GetDeadAnimTime() < m_fDeadAnimTimer)
	{
		DeleteObject(pMonster);
	}
}
