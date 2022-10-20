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
}

void CAttackState::Exit()
{
}

void CAttackState::update()
{
	// 몬스터별 공격 처리
	GetAI()->GetOwner()->Attack();


}
