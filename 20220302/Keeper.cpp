#include "pch.h"
#include "Keeper.h"

CKeeper::CKeeper()
	: m_fAttackCooldown(0.f)
	, m_fMoveCooldown(0.f)
	, m_pTearTex(nullptr)
	, m_pShadowTex(nullptr)
	, m_vJumpDest()
	, m_vJumpDir()
	, m_bDefinePos()

{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"KeeperTex", L"texture\\Monster\\monster_152_keeper.bmp");
	m_pTearTex = CResMgr::GetInst()->LoadTexture(L"TearTexBlood", L"texture\\Tear\\effect_012_poof04.bmp");
	m_pShadowTex = CResMgr::GetInst()->LoadTexture(L"shadowTex", L"texture\\shadow.bmp");

	m_strAnimName = L"KEEPER_IDLE";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"KEEPER_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 1, false);


	m_vAnimOffset = Vec2(-12.f, -12.f);	

	PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
}

CKeeper::~CKeeper()
{
}

void CKeeper::update()
{
	if (GetOwner()->GetOwner()->GetCurrentRoom() == GetOwner())
	{
		m_fMoveCooldown += fDT;
		m_fAttackCooldown += fDT;


			if (2.3f < m_fMoveCooldown)
			{
				if (!m_bDefinePos)
				{
					void* p = new int();
					void* q = new int();
					srand((int)p);

					int iToPlayer = rand() % 3;
					if (0 == iToPlayer)
					{
						m_vJumpDest = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetPos();
					}
					else
					{
 
						m_vJumpDest = Vec2(rand() % 901 - 450, rand() % 431 - 215);
						Vec2 vTemp = GetOwner()->GetPos();
						m_vJumpDest += vTemp;
						while (true)
						{
							if (!CSceneMgr::GetInst()->GetCurScene()->CheckObject(m_vJumpDest, GetCollider()->GetScale()))
								break;
							else
							{
								m_vJumpDest = Vec2(rand() % 901 - 450, rand() % 431 - 215);
								Vec2 vTemp = GetOwner()->GetPos();
								m_vJumpDest += vTemp;
							}
						}
					}

					m_vJumpDir = m_vJumpDest - GetPos();
					m_vJumpDir.Normalize();

					delete p;

					m_bDefinePos = true;
				}
				if (m_bDefinePos)
				{
					m_bOnAir = true;
					GetRigidBody()->SetVelocity(m_vJumpDir * 500.f);
				}

			}
			if (m_bOnAir)
			{
				if (2.3f < m_fMoveCooldown && 2.5f > m_fMoveCooldown)
				{
					m_vAnimOffset.x = 0.f;
					m_vAnimOffset.y -= (400.f * fDT);
					GetAnimator()->GetCurAnim()->SetOffset(Vec2(m_vAnimOffset.x, m_vAnimOffset.y));
				}
				if (2.5f < m_fMoveCooldown && 2.7f > m_fMoveCooldown)
				{
					m_vAnimOffset.x = 0.f;
					m_vAnimOffset.y += (400.f * fDT);
					GetAnimator()->GetCurAnim()->SetOffset(Vec2(m_vAnimOffset.x, m_vAnimOffset.y));
				}
			}
			if (2.7f < m_fMoveCooldown)
			{
				GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));

				m_fAttackCooldown = 0.f;
				m_fMoveCooldown = 0.f;
				m_bOnAir = false;
				m_bDefinePos = false;
				m_vJumpDir = { 0.f ,0.f };
				m_vJumpDest = { 0.f ,0.f };
				m_vAnimOffset = Vec2(-12.f, -12.f);	
			}
		

		CMonster::update();
	}
}

void CKeeper::render(HDC _dc)
{
	if (CSceneMgr::GetInst()->GetCurScene()->GetMap()->GetCurrentRoom() == GetOwner())
	{
		int iWidth = static_cast <int>(m_pShadowTex->GetWidth());
		int iHeight = static_cast<int>(m_pShadowTex->GetHeight());
		Vec2 vScale = GetScale();
		Vec2 vPos = GetPos();
		vPos = CCamera::GetInst()->GetRenderPos(vPos);


		TransparentBlt(_dc
			, static_cast<int>(vPos.x - (vScale.x / 2))
			, static_cast<int>(vPos.y - (vScale.y / 2)) + 55
			, 60, 24
			, m_pShadowTex->GetDC()
			, 0, 0, 120, 49
			, RGB(255, 0, 255));


		//BLENDFUNCTION bf = {};

		//bf.BlendOp = AC_SRC_OVER;
		//bf.BlendFlags = 0;
		//bf.AlphaFormat = 0;
		//bf.SourceConstantAlpha = 255;

		//AlphaBlend(_dc
		//	, static_cast<int>(vPos.x - (vScale.x / 2))
		//	, static_cast<int>(vPos.y - (vScale.y / 2)) + 55
		//	, 60, 24
		//	, m_pShadowTex->GetDC()
		//	, 0, 0, 120, 49
		//	, bf
		//);

		component_render(_dc);

	}
}

void CKeeper::Attack()
{
	if (m_fAttackCooldown > 1.5f)
	{
		Vec2 vTargetDir = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetCollider()->GetFinalPos() - GetPos();
		vTargetDir = vTargetDir.Normalize();
		for (int i = -1; i < 2; i++)
		{
			if (0 == i)
				continue;

			CreateMissile(vTargetDir.Rotate(20 * i), m_pTearTex, L"Keeper");
		}

		GetAI()->ChangeState(MON_STATE::IDLE);
		m_fAttackCooldown = 0;
	}
}
