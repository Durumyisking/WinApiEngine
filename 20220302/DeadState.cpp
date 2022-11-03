#include "pch.h"
#include "DeadState.h"
#include "Monster.h"
#include "Collider.h"
#include "RigidBody.h"


CDeadState::CDeadState()
	: CState(MON_STATE::DEAD)
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
		pMonster->PlayAnim(pMonster->GetAnimInstance(), pMonster->GetCurrentAnim(), pMonster->GetAnimOffset(), false);

		if (pMonster->GetCollider()->IsOn())
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
		CMonster* pMonster = GetMonster();

		if(pMonster->GetCollider()->IsOn())
			pMonster->GetCollider()->SwitchOff();

		if(pMonster->GetAnimator()->GetCurAnim()->IsFinish())
		{
			// ���� ������ ��ü ������ ȿ�� ����

			DeleteObject(pMonster);
		}
}
