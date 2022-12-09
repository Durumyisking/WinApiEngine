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
	// �����ִϸ��̼� ������ ���� �ִϸ��̼� ����
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
		CParticleMgr::GetInst()->CreateParticle(PARTICLE_TYPE::bloodgibs, GetMonster()->GetPos());
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
			// ���� ������ ��ü ������ ȿ�� ����
			CParticleMgr::GetInst()->CreateParticle(PARTICLE_TYPE::bloodgibs, GetMonster()->GetPos());
			DeleteObject(pMonster);
		}
}
