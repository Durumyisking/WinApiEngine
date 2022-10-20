#include "pch.h"
#include "AttackState.h"
#include "Monster.h"
CAttackState::CAttackState()
	: CState(MON_STATE::ATTACK)
{

}

CAttackState::~CAttackState()
{
}

void CAttackState::Enter()
{
	CMonster* pMonster = GetMonster();
	if (L"" != pMonster->GetAnimName(MON_STATE::ATTACK))
	{
		pMonster->SetCurrentAnim(pMonster->GetAnimName(MON_STATE::ATTACK));
		pMonster->PlayAnim(pMonster->GetAnimInstance(), pMonster->GetCurrentAnim(), Vec2(0.f, 0.f), true);
	}
}

void CAttackState::Exit()
{
}

void CAttackState::update()
{
	// 몬스터별 공격 처리
	GetAI()->GetOwner()->Attack();


}
