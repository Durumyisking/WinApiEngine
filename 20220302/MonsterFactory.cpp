#include "pch.h"
#include "MonsterFactory.h"
#include "Monster.h"

#include "AI.h"
#include "IdleState.h"
#include "TraceState.h"
#include "AttackState.h"
#include "PatrolState.h"
#include "DeadState.h"

#include "RigidBody.h"
#include "Room.h"

#include "Gaper.h"
#include "Fly.h"
#include "Host.h"

CMonster * CMonsterFactory::CreateMonster(MON_TYPE _eType, Vec2 _vPos, CRoom* _pRoom)
{
	CMonster* pMon = nullptr;

	switch (_eType)
	{
	case MON_TYPE::Gaper:
	{
		pMon = new CGaper;
		Stat Stat = { 30, 30, 1, 300.f, 0.f, 0.f , 0.f };
		pMon->SetScale(Vec2(90.f, 114.f));
		pMon->SetStat(Stat);
		pMon->SetRecogRange(200.f);
		pMon->SetPos(_vPos);
		pMon->SetOwner(_pRoom);


		CAI* pAI = new CAI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceState);

		pAI->SetCurState(MON_STATE::IDLE);
		pMon->SetAI(pAI);

		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		pMon->GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
		pMon->GetCollider()->SetScale(Vec2(80.f, 100.f));

	}
		break;

	case MON_TYPE::Fly:
	{
		pMon = new CFly;
		Stat Stat = { 10, 10, 1, 100.f, 0.f, 0.f , 0.f };
		pMon->SetScale(Vec2(32.f, 32.f));
		pMon->SetStat(Stat);
		pMon->SetRecogRange(300.f);
		pMon->SetPos(_vPos);
		pMon->SetOwner(_pRoom);
		pMon->SetDeadAnimTime(0.6f);

		CAI* pAI = new CAI;
		pAI->AddState(new CPatrolState);
		pAI->AddState(new CTraceState);


		pAI->SetCurState(MON_STATE::PATROL);
		pMon->SetAI(pAI);

		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);
		pMon->GetRigidBody()->SetFricCoeff(0.f);

		pMon->GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
		pMon->GetCollider()->SetScale(Vec2(32.f, 32.f));

	}
		break;

	case MON_TYPE::Host:
	{
		pMon = new CHost;
		Stat Stat = { 30, 30, 1, 0.f, 1200.f, 3.f ,0.f };
		pMon->SetScale(Vec2(32.f, 64.f));
		pMon->SetStat(Stat);
		pMon->SetRecogRange(150.f);
		pMon->SetPos(_vPos);
		pMon->SetOwner(_pRoom);


		CAI* pAI = new CAI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CAttackState);

		pAI->SetCurState(MON_STATE::IDLE);
		pMon->SetAI(pAI);

		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		pMon->GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
		pMon->GetCollider()->SetScale(Vec2(64.f, 64.f));

	}
	break;
	default:
		break;
	}
	
	// 모든 몬스터는 죽음
	pMon->GetAI()->AddState(new CDeadState);

	return pMon;
}

CMonsterFactory::CMonsterFactory()
{


}
