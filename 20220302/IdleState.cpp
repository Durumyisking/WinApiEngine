#include "pch.h"
#include "IdleState.h"

CIdleState::CIdleState()
	: CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}

void CIdleState::update()
{
	// player의 위치 체크

	// 몬스터 범위 안에 들어오면 추적상태로 전환

	// 

}
