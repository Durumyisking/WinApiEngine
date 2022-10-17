#include "pch.h"
#include "MonsterFactory.h"
#include "Monster.h"

#include "AI.h"
#include "IdleState.h"
#include "TraceState.h"

#include "RigidBody.h"

#include "Gaper.h"


CMonster * CMonsterFactory::CreateMonster(MON_TYPE _eType, Vec2 _vPos)
{
	CMonster* pMon = nullptr;
	switch (_eType)
	{
	case MON_TYPE::Gaper:
	{
		pMon = new CGaper;
		Stat GaperStat = { 30, 30, 1, 100.f, 650.f, 0.38f };
		pMon->SetScale(Vec2(90.f, 114.f));
		pMon->SetStat(GaperStat);
		pMon->SetRecogRange(250.f);

		pMon->SetPos(_vPos);

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

	case MON_TYPE::RANGE:
		break;
	default:
		break;
	}
	

	return pMon;
}

CMonsterFactory::CMonsterFactory()
{


}
