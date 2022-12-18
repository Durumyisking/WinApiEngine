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
	CMonster* pMonster = GetMonster();
	if (L"" != pMonster->GetAnimName(MON_STATE::TRACE))
	{
		pMonster->SetCurrentAnim(pMonster->GetAnimName(MON_STATE::TRACE));
		pMonster->PlayAnim(pMonster->GetAnimInstance(), pMonster->GetCurrentAnim(), pMonster->GetAnimOffset(), true);
	}

}

void CTraceState::Exit()
{

}

void CTraceState::update()
{
	//follow player
	CPlayer* pPlayer;
	pPlayer = CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetCollider()->GetFinalPos();
	Vec2 vMonsterPos = GetMonster()->GetPos();

	// ���Ͱ� �̵��� ����
	Vec2 vMonDir = vPlayerPos - vMonsterPos;
	vMonDir.Normalize();
	vMonDir = vMonDir * GetMonster()->GetStat().m_fSpeed;
	GetMonster()->GetRigidBody()->SetVelocity(vMonDir);

//	vMonsterPos += vMonDir * GetMonster()->GetStat().m_fSpeed * fDT;

//	GetMonster()->SetPos(vMonsterPos);

}
