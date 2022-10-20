#include "pch.h"
#include "DeadState.h"
#include "Monster.h"
#include "Collider.h"


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
	// �����ִϸ��̼� ������ ���� �ִϸ��̼� ����
	if (L"" != pMonster->GetDeadAnimName())
	{
		pMonster->SetCurrentAnim(pMonster->GetDeadAnimName());
		pMonster->PlayAnim(pMonster->GetAnimInstance(), pMonster->GetCurrentAnim(), Vec2(0.f, 0.f), false);
		pMonster->GetCollider()->SwitchOff();
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
