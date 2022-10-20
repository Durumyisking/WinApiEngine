#include "pch.h"
#include "IdleState.h"

#include "Scene.h"
#include "SceneMgr.h"

#include "Player.h"
#include "Monster.h"

#include "Core.h"

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
	// player�� ��ġ üũ
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();



	// ���� ���� �ȿ� ������ �������·� ��ȯ
	CMonster* pMonster = GetMonster();
	float fRecogrange =  pMonster->GetRecogRange();
	Vec2 vMonPos = pMonster->GetPos();

	Vec2 fDiff = vPlayerPos - vMonPos;
	float fLen = fDiff.Length();

	if (fLen < fRecogrange)
	{
		if(nullptr != GetAI()->GetState(MON_STATE::TRACE))
			ChangeAIState(GetAI(), MON_STATE::TRACE);
		if (nullptr != GetAI()->GetState(MON_STATE::ATTACK))
			ChangeAIState(GetAI(), MON_STATE::ATTACK);

	}

}
