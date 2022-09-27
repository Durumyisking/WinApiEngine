#include "pch.h"
#include "State.h"

#include "AI.h"
#include "Monster.h"

CState::CState(MON_STATE _eState)
{
	m_eState = _eState;
}

CState::~CState()
{
}

CMonster* CState::GetMonster()
{
	return m_pAI->GetOwner();
}
