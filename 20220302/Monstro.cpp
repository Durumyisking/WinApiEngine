#include "pch.h"
#include "Monstro.h"

CMonstro::CMonstro()
	: m_fAttackCooldown(0.f)
	, m_fAttackPrePare(0.f)
	, m_fPostTimer(0.f)
	, m_eState(MONSTRO_STATE::IDLE)
	, m_bAnimPlaying(false)
	, m_pTearTex(nullptr)
	, m_vTargetDir()
	, m_vAnimOffsetTemp()
	, m_fTrumble(5.f)
	, m_fShotgun(0.f)
	, bDefinePos(false)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"MonstroTex", L"texture\\Boss\\boss_004_monstro.bmp");
	m_pTearTex = CResMgr::GetInst()->LoadTexture(L"TearTexBlood", L"texture\\Tear\\effect_012_poof04.bmp");
	m_pShadowTex = CResMgr::GetInst()->LoadTexture(L"shadowTex", L"texture\\shadow.bmp");

	m_strAnimName = L"MONSTRO_IDLE";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"MONSTRO_IDLE", m_pTex, Vec2(160.f, 0.f), Vec2(80.f, 112.f), Vec2(80.f, 0.f), 1.f, 1, false);
	GetAnimator()->CreateAnimation(L"MONSTRO_BEFOREATTACK", m_pTex, Vec2(160.f, 0.f), Vec2(80.f, 112.f), Vec2(80.f, 0.f), 0.5f, 1, false);
	GetAnimator()->CreateAnimation(L"MONSTRO_PREFIRE", m_pTex, Vec2(80.f, 0.f), Vec2(80.f, 112.f), Vec2(80.f, 0.f), 1.1f, 1, false);
	GetAnimator()->CreateAnimation(L"MONSTRO_FIRE", m_pTex, Vec2(240.f, 0.f), Vec2(80.f, 112.f), Vec2(80.f, 0.f), 2.f, 1, false);
	GetAnimator()->CreateAnimation(L"MONSTRO_PREJUMP", m_pTex, Vec2(0.f, 112.f), Vec2(80.f, 112.f), Vec2(80.f, 0.f), 0.3f, 1, false);
	GetAnimator()->CreateAnimation(L"MONSTRO_JUMP", m_pTex, Vec2(80.f, 112.f), Vec2(80.f, 112.f), Vec2(80.f, 0.f), 1.f, 1, false);
	GetAnimator()->CreateAnimation(L"MONSTRO_FALL", m_pTex, Vec2(320.f, 0.f), Vec2(80.f, 112.f), Vec2(80.f, 0.f), 1.125f, 1, false);
	GetAnimator()->CreateAnimation(L"MONSTRO_JUMPAIR", m_pTex, Vec2(160.f, 112.f), Vec2(80.f, 112.f), Vec2(80.f, 0.f), 1.f, 1, false);

	GetAnimator()->CreateAnimation(L"MONSTRO_DEAD", m_pTex, Vec2(240.f, 112.f), Vec2(80.f, 112.f), Vec2(80.f, 0.f), 0.25f, 8, false);


	m_arrAnimName[static_cast<UINT>(MON_STATE::IDLE)] = L"MONSTRO_IDLE";
	m_arrAnimName[static_cast<UINT>(MON_STATE::DEAD)] = L"MONSTRO_DEAD";

	m_vAnimOffset = Vec2(-40.f, -160.f);

	PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
	m_bAnimPlaying = true;
	m_bDeadAnim = false;
}

CMonstro::~CMonstro()
{
}

void CMonstro::update()
{
	if (GetOwner()->GetOwner()->GetCurrentRoom() == GetOwner())
	{
		if (0 < m_Stat.m_iHP)
		{
			if (m_eState == MONSTRO_STATE::IDLE)
			{
				m_fAttackCooldown += fDT;

				// idle 2초 지속시 공격
				if (m_fAttackCooldown > 1.f)
				{
					m_vAnimOffsetTemp = m_vAnimOffset;

					m_eState = MONSTRO_STATE::BEFOREATTACK;
					m_bAnimPlaying = false;
					m_fAttackCooldown = 0.f;

				}
			}
			if (m_eState == MONSTRO_STATE::BEFOREATTACK)
			{
				// 처음 들어왔을때
				if (!m_bAnimPlaying)
				{
					m_strAnimName = L"MONSTRO_BEFOREATTACK";
					PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, false);
					m_bAnimPlaying = true;
				}
				// 애니메이션 끝나면 ATTACKPRE로
				if (GetAnimator()->GetCurAnim()->IsFinish())
				{
					GetAnimator()->GetCurAnim()->SetFrame(0);
					// idle 1초 지속시 공격
					void* p = new int();
					srand((int)p);

					int iflag1 = static_cast<int>(rand() % 3);
					if (0 == iflag1)
					{
						m_strAnimName = L"MONSTRO_PREFIRE";
						m_eState = MONSTRO_STATE::FIREPRE;
						PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
					}
					if (1 == iflag1)
					{
						m_strAnimName = L"MONSTRO_PREJUMP";
						m_eState = MONSTRO_STATE::BIGJUMPPRE;
						PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
					}
					if (2 == iflag1)
					{
						m_strAnimName = L"MONSTRO_PREJUMP";
						m_eState = MONSTRO_STATE::JUMPPRE;
						PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
					}

				}			
			}
			if (m_eState == MONSTRO_STATE::FIREPRE)
			{
				m_fAttackPrePare += fDT;
				// 1초간 공격 준비
				if (m_fAttackPrePare > 0.5f)
				{
					m_eState = MONSTRO_STATE::FIRE;
					m_bAnimPlaying = false;
					m_fAttackPrePare = 0.f;
				}
			}

			if (m_eState == MONSTRO_STATE::FIRE)
			{
				// 처음 들어왔을때
				if (!m_bAnimPlaying)
				{
					m_strAnimName = L"MONSTRO_FIRE";
					PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, false);
					m_bAnimPlaying = true;
					m_vTargetDir = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetCollider()->GetFinalPos() - GetPos();
					m_vTargetDir.Normalize();

				}
				else
				{
					Shotgun();
				}

				GetAnimator()->GetCurAnim()->SetOffset(Vec2(m_fTrumble, 0.f));
				m_fTrumble *= -1;

				// 애니메이션 끝나면 IDLE로
				if (GetAnimator()->GetCurAnim()->IsFinish())
				{
					GetAnimator()->GetCurAnim()->SetFrame(0);

					GetAnimator()->GetCurAnim()->SetOffset(Vec2(m_vAnimOffset.x - m_fTrumble, 0.f));
					m_eState = MONSTRO_STATE::IDLE;
					m_strAnimName = L"MONSTRO_IDLE";
					PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
				}

			}


			if (m_eState == MONSTRO_STATE::BIGJUMPPRE)
			{
				m_fAttackPrePare += fDT;
				// 1초간 공격 준비
				if (m_fAttackPrePare > 0.5f)
				{
					m_eState = MONSTRO_STATE::BIGJUMP;
					m_bAnimPlaying = false;
					m_fAttackPrePare = 0.f;
				}
			}

			if (m_eState == MONSTRO_STATE::BIGJUMP)
			{
				// 처음 들어왔을때
				if (!m_bAnimPlaying)
				{
					m_strAnimName = L"MONSTRO_JUMP";
					PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, false);
					m_bAnimPlaying = true;
					m_bOnAir = true;
					GetCollider()->SwitchOff();

				}
				else
				{
					m_vAnimOffset.y  = m_vAnimOffset.y - (1000.f * fDT);
					GetAnimator()->GetCurAnim()->SetOffset(Vec2(0.f, m_vAnimOffset.y));
				} 

				if (GetAnimator()->GetCurAnim()->IsFinish())
				{
					m_vTargetPos = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetCollider()->GetFinalPos();
					SetPos(m_vTargetPos);
					GetAnimator()->GetCurAnim()->SetFrame(0);
					m_eState = MONSTRO_STATE::FALL;
					m_strAnimName = L"MONSTRO_FALL";
					PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, false);

				}
			}

			if (m_eState == MONSTRO_STATE::FALL)
			{
				m_vAnimOffset.y = m_vAnimOffset.y + (2000.f * fDT);
				GetAnimator()->GetCurAnim()->SetOffset(Vec2(0.f, m_vAnimOffset.y));

				if (GetAnimator()->GetCurAnim()->IsFinish())
				{
					//m_vTargetDir = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetCollider()->GetFinalPos() - GetPos();
					//m_vTargetDir.Normalize();
					//LandSpray();

					m_vAnimOffset = m_vAnimOffsetTemp;
					GetAnimator()->GetCurAnim()->SetFrame(0);
					m_eState = MONSTRO_STATE::FALLEND;
					m_strAnimName = L"MONSTRO_PREJUMP";
					PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, false);
					GetCollider()->SwitchOn();

				}

			}

			if (m_eState == MONSTRO_STATE::FALLEND)
			{
				// 애니메이션 끝나면 IDLE로
				if (GetAnimator()->GetCurAnim()->IsFinish())
				{
					GetAnimator()->GetCurAnim()->SetFrame(0);
					m_eState = MONSTRO_STATE::IDLE;
					m_strAnimName = L"MONSTRO_IDLE";
					PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
				}
			}
		}


		if (m_eState == MONSTRO_STATE::JUMPPRE)
		{
			m_fAttackPrePare += fDT;
			// 1초간 공격 준비
			if (m_fAttackPrePare > 0.5f)
			{
				m_eState = MONSTRO_STATE::JUMP;
				m_bAnimPlaying = false;
				m_fAttackPrePare = 0.f;
			}
		}

		if (m_eState == MONSTRO_STATE::JUMP)
		{
			m_fJumpTimer += fDT;

			// 처음 들어왔을때
			if (!m_bAnimPlaying)
			{
				m_strAnimName = L"MONSTRO_JUMP";
				PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
				m_bAnimPlaying = true;
				m_vAnimOffsetTemp = m_vAnimOffset;
			}

			if (0.1f < m_fJumpTimer)
			{
				if (!bDefinePos)
				{
					m_bOnAir = true;
					GetCollider()->SwitchOff();

					vJumpDest = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetPos();
					vJumpDir = vJumpDest - GetPos();
					vJumpDir.Normalize();
					bDefinePos = true;
					m_strAnimName = L"MONSTRO_JUMPAIR";
					PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, false);
				}
			}

			if (m_bOnAir)
			{
				GetRigidBody()->SetVelocity(vJumpDir * 300.f);

				if (0.3f < m_fJumpTimer && 0.6f > m_fJumpTimer)
				{
					m_vAnimOffset.x = 0.f;
					m_vAnimOffset.y -= (300.f * fDT);
					GetAnimator()->GetCurAnim()->SetOffset(Vec2(m_vAnimOffset.x, m_vAnimOffset.y));
				}
				if (0.6f < m_fJumpTimer && 0.9f > m_fJumpTimer)
				{
					m_vAnimOffset.x = 0.f;
					m_vAnimOffset.y += (300.f * fDT);
					GetAnimator()->GetCurAnim()->SetOffset(Vec2(m_vAnimOffset.x, m_vAnimOffset.y));
				}
			}
			if (0.9f < m_fJumpTimer)
			{
				GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));

				m_fAttackCooldown = 0.f;
				m_bOnAir = false;
				bDefinePos = false;
				m_vAnimOffset = m_vAnimOffsetTemp;
				GetCollider()->SwitchOn();

				GetAnimator()->GetCurAnim()->SetFrame(0);
				m_strAnimName = L"MONSTRO_FALL";
				PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
			}
			if (1.f < m_fJumpTimer)
			{
				m_fJumpTimer = 0.f;
				m_eState = MONSTRO_STATE::IDLE;
				m_strAnimName = L"MONSTRO_IDLE";
				PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);

			}

		}

		CMonster::update();
	}
}

void CMonstro::render(HDC _dc)
{

	if (CSceneMgr::GetInst()->GetCurScene()->GetMap()->GetCurrentRoom() == GetOwner())
	{
		if (m_bOnAir)
		{
			int iWidth = static_cast <int>(m_pShadowTex->GetWidth());
			int iHeight = static_cast<int>(m_pShadowTex->GetHeight());
			Vec2 vScale = GetScale();
			Vec2 vPos = GetPos();
			vPos = CCamera::GetInst()->GetRenderPos(vPos);


			TransparentBlt(_dc
				, static_cast<int>(vPos.x - (vScale.x / 2))
				, static_cast<int>(vPos.y - (vScale.y / 2)) + 55
				, 120, 48
				, m_pShadowTex->GetDC()
				, 0, 0, 120, 49
				, RGB(255, 0, 255));


		/*	BLENDFUNCTION bf = {};

			bf.BlendOp = AC_SRC_OVER;
			bf.BlendFlags = 0;
			bf.AlphaFormat = 0;
			bf.SourceConstantAlpha = 128;

			AlphaBlend(_dc
				, static_cast<int>(vPos.x - (vScale.x / 2))
				, static_cast<int>(vPos.y - (vScale.y / 2)) + 55
				, 120, 48
				, m_pShadowTex->GetDC()
				, 0, 0, 120, 49
				, bf
			);*/

		}
		component_render(_dc);
	}
}

void CMonstro::Attack()
{
}

void CMonstro::Shotgun()
{
	void* p = new int();
	for (int i = 0; i < 3; i++)
	{
		srand((int)p);
		int shotflag = static_cast<int>(rand() % 7);
		if (0 == shotflag)
		{
			int degree = static_cast<int>(rand() % 21) - 10;
			float range = static_cast<float>(rand() % 30) / 10;
			m_Stat.m_fRange = range;

			CreateMissile(m_vTargetDir.Rotate(degree), m_pTearTex, L"Monstro");
		}
		else
		{
			continue;
		}
	}
}

void CMonstro::LandSpray()
{
	//void* p = new int();
	//for (int i = 0; i < 20; i++)
	//{
	//	srand((int)p);

	//	int degree = static_cast<int>(rand() % 360);
	//	float range = static_cast<float>(rand() % 30) / 10;
	//	m_Stat.m_fRange = range;

	//	CreateMissile(m_vTargetDir.Rotate(degree), m_pTearTex, L"Monstro");
	//}
	//delete p;
}
