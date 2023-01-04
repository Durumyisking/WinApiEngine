#include "pch.h"
#include "Sucker.h"

CSucker::CSucker()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"SuckerTex", L"texture\\Monster\\monster_078_sucker.bmp");
	m_pTearTex = CResMgr::GetInst()->LoadTexture(L"TearTexBlood", L"texture\\Tear\\effect_012_poof04.bmp");

	m_strAnimName = L"Sucker_PATROL";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Sucker_PATROL", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.01f, 2, false);
	GetAnimator()->FindAnimation(L"Sucker_PATROL")->SetMagnify(2.f);

	m_arrAnimName[static_cast<UINT>(MON_STATE::IDLE)] = L"Sucker_PATROL";
	PlayAnim(m_pAnim, m_strAnimName, Vec2(-4.f, 0.f), true);

	m_bNoparticle = true;
}

CSucker::~CSucker()
{
}

void CSucker::update()
{
	if (GetOwner()->GetOwner()->GetCurrentRoom() == GetOwner())
	{
		if (0 >= m_Stat.m_iHP)
		{
			for (int i = 0; i < 3; i++)
			{
				CreateMissile(Vec2(0.f ,1.f), m_pTearTex, L"Sucker");
				CreateMissile(Vec2(0.f, -1.f), m_pTearTex, L"Sucker");
				CreateMissile(Vec2(1.f, 0.f), m_pTearTex, L"Sucker");
				CreateMissile(Vec2(-1.f, 0.f), m_pTearTex, L"Sucker");
			}

		}


		CMonster::update();
	}

}

void CSucker::Attack()
{

}
