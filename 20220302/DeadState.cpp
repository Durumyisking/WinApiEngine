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
	// 죽음애니메이션 있으면 죽음 애니메이션 실행
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
			// 몬스터 죽을때 시체 나가는 효과 넣자

			DeleteObject(pMonster);
		}
}
