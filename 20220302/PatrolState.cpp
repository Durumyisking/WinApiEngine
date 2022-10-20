#include "pch.h"
#include "PatrolState.h"
#include "TimeMgr.h"
#include "RigidBody.h"
#include "Object.h"
#include "Monster.h"
#include "Scene.h"
#include "SceneMgr.h"

CPatrolState::CPatrolState()
	: CState(MON_STATE::PATROL)
{
}

CPatrolState::~CPatrolState()
{
}

void CPatrolState::Enter()
{
	CMonster* pMonster = GetMonster();
	if (L"" != pMonster->GetAnimName(MON_STATE::PATROL))
	{
		pMonster->SetCurrentAnim(pMonster->GetAnimName(MON_STATE::PATROL));
		pMonster->PlayAnim(pMonster->GetAnimInstance(), pMonster->GetCurrentAnim(), Vec2(0.f, 0.f), true);
	}
}

void CPatrolState::Exit()
{
}

void CPatrolState::update()
{
	// player의 위치 체크
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	// 몬스터 범위 안에 들어오면 추적상태로 전환
	CMonster* pMonster = GetMonster();
	float fRecogrange = pMonster->GetRecogRange();
	Vec2 vMonPos = pMonster->GetPos();

	Vec2 fDiff = vPlayerPos - vMonPos;
	float fLen = fDiff.Length();

	if (fLen < fRecogrange)
	{
		if (nullptr != GetAI()->GetState(MON_STATE::TRACE))
			ChangeAIState(GetAI(), MON_STATE::TRACE);
		if (nullptr != GetAI()->GetState(MON_STATE::ATTACK))
			ChangeAIState(GetAI(), MON_STATE::ATTACK);

	}
	else
	{
		srand(CTimeMgr::GetInst()->GetCurCount());
		float x = static_cast<float>(rand() % 1000 - 500);
		srand(CTimeMgr::GetInst()->GetCurCount() * CTimeMgr::GetInst()->GetCurCount());
		float y = static_cast<float>(rand() % 1000 - 500);
		GetMonster()->GetRigidBody()->AddForce(Vec2(x, y));
	}

}
