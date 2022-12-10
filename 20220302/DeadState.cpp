#include "pch.h"
#include "DeadState.h"
#include "Monster.h"
#include "Collider.h"
#include "RigidBody.h"
#include "ParticleMgr.h"
#include "Particle.h"

CDeadState::CDeadState()
	: CState(MON_STATE::DEAD)
{
}

CDeadState::~CDeadState()
{
}

void CDeadState::Enter()
{
	CMonster* pMonster = GetMonster();
	// 죽음애니메이션 있으면 죽음 애니메이션 실행
	if (L"" != pMonster->GetAnimName(MON_STATE::DEAD))
	{
		pMonster->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
		pMonster->SetCurrentAnim(pMonster->GetAnimName(MON_STATE::DEAD));
		pMonster->PlayAnim(pMonster->GetAnimInstance(), pMonster->GetCurrentAnim(), pMonster->GetAnimOffset(), false);

		if (pMonster->GetCollider()->IsOn())
			pMonster->GetCollider()->SwitchOff();

	}
	else
	{
		CParticleMgr::GetInst()->CreateParticle(PARTICLE_TYPE::bloodpool, GetMonster()->GetPos(), Vec2(0.f, 0.f));
		for (int i = -1; i <= 1; i++)
		{
			if (0 == i)
				continue;
			for (int j = -1; j <= 1; j++)
			{
				if (0 == j)
					continue;

				CParticleMgr::GetInst()->CreateParticle(PARTICLE_TYPE::bloodgibs, GetMonster()->GetPos() + Vec2(i * 15.f, j * 15.f), Vec2(i, j));
			}
		}
		DeleteObject(pMonster);
	}
}

void CDeadState::Exit()	
{
}

void CDeadState::update()
{
		CMonster* pMonster = GetMonster();

		if(pMonster->GetCollider()->IsOn())
			pMonster->GetCollider()->SwitchOff();

		if(pMonster->GetAnimator()->GetCurAnim()->IsFinish())
		{
			// 몬스터 죽을때 시체 나가는 효과 넣자
			CParticleMgr::GetInst()->CreateParticle(PARTICLE_TYPE::bloodpool, GetMonster()->GetPos(), Vec2(0.f,0.f));
			for (int i = -1; i <= 1; i++)
			{
				if (0 == i)
					continue;
				for (int j = -1; j <= 1; j++)
				{
					if (0 == j)
						continue;
					
					CParticleMgr::GetInst()->CreateParticle(PARTICLE_TYPE::bloodgibs, GetMonster()->GetPos() + Vec2(i*50.f, j*50.f), Vec2(i, j));
				}
			}
			DeleteObject(pMonster);
		}
}
