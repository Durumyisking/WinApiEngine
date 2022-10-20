#include "pch.h"
#include "PatrolState.h"
#include "TimeMgr.h"
#include "RigidBody.h"
#include "Object.h"
#include "Monster.h"

CPatrolState::CPatrolState()
	: CState(MON_STATE::PATROL)
{
}

CPatrolState::~CPatrolState()
{
}

void CPatrolState::Enter()
{
}

void CPatrolState::Exit()
{
}

void CPatrolState::update()
{
	srand(CTimeMgr::GetInst()->GetCurCount());
	float x = static_cast<float>(rand() % 1000 - 500);
	srand(CTimeMgr::GetInst()->GetCurCount() * CTimeMgr::GetInst()->GetCurCount());
	float y = static_cast<float>(rand() % 1000 - 500);
	GetMonster()->GetRigidBody()->AddForce(Vec2(x, y));

}
