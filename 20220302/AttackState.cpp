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
	// ���ͺ� ���� ó��
	GetAI()->GetOwner()->Attack();


}
