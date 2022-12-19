#include "pch.h"
#include "Coltty.h"

CColtty::CColtty()
	: m_fAttackCooldown(0.f)
	, m_pTearTex(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"ColttyTex", L"texture\\Monster\\monster_065_clotty.bmp");
	m_pTearTex = CResMgr::GetInst()->LoadTexture(L"TearTexBlood", L"texture\\Tear\\effect_012_poof04.bmp");

	m_strAnimName = L"COLTTY_IDLE";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"COLTTY_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.05f, 11, false);

	m_arrAnimName[static_cast<UINT>(MON_STATE::IDLE)] = L"COLTTY_IDLE";

	PlayAnim(m_pAnim, m_strAnimName, Vec2(-48.f, -48.f), true);
}

CColtty::~CColtty()
{
}

void CColtty::update()
{
	m_fAttackCooldown += fDT;

	CMonster::update();

}

void CColtty::Attack()
{
	if (GetOwner()->GetOwner()->GetCurrentRoom() == GetOwner())
	{
		if (1.5f < m_fAttackCooldown)
		{
			Vec2 vDir = Vec2(0.f, 0.f);
			for (UINT i = 0; i < static_cast<UINT>(DIR::END); i++)
			{

				switch (i)
				{
				case static_cast<UINT>(DIR::RIGHT):
					vDir = Vec2(1.f, 0.f);
					break;
				case static_cast<UINT>(DIR::LEFT):
					vDir = Vec2(-1.f, 0.f);
					break;
				case static_cast<UINT>(DIR::UP):
					vDir = Vec2(0.f, -1.f);
					break;
				case static_cast<UINT>(DIR::DOWN):
					vDir = Vec2(0.f, 1.f);
					break;

				default:
					break;
				}


				CreateMissile(vDir, m_pTearTex, L"Coltty");
			}

			m_fAttackCooldown = 0.f;
		}


		srand(CTimeMgr::GetInst()->GetCurCount());
		float x = static_cast<float>(rand() % 10000 - 4800);
		srand(CTimeMgr::GetInst()->GetCurCount() * CTimeMgr::GetInst()->GetCurCount());
		float y = static_cast<float>(rand() % 10000 - 4800);
		GetRigidBody()->AddForce(Vec2(x, y));
	}
}

void CColtty::OnCollision(CCollider* _pOther)
{
	CMonster::OnCollision(_pOther);
}

void CColtty::OnCollisionEnter(CCollider* _pOther)
{
	CMonster::OnCollisionEnter(_pOther);
}

void CColtty::OnCollisionExit(CCollider* _pOther)
{
	CMonster::OnCollisionExit(_pOther);
 }
