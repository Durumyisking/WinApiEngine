#include "pch.h"
#include "TraceState.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Player.h"
#include "Monster.h"

#include "TimeMgr.h"

CTraceState::CTraceState()
	: CState(MON_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Enter()
{

}

void CTraceState::Exit()
{

}

void CTraceState::update()
{
	//follow player
	CPlayer* pPlayer;
	pPlayer = CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vMonsterPos = GetMonster()->GetPos();

	// 몬스터가 이동할 방향
	Vec2 vMonDir = vPlayerPos - vMonsterPos;
	vMonDir.Normalize();
	vMonsterPos += vMonDir * GetMonster()->GetStat().m_fSpeed * fDT;

	GetMonster()->SetPos(vMonsterPos);

}
