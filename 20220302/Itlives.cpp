#include "pch.h"
#include "Itlives.h"

CItlives::CItlives()
	: m_fAttackCooldown(3.f)
	, m_fBeatCooldown(3.f)
	, m_bInvisible(false)
	, m_bMove(false)
	, m_bTargetDefine(false)
	, m_iPatternCount(0)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"ItlivesTex", L"texture\\Boss\\boss_070_itlives.bmp");
	m_pTearTex = CResMgr::GetInst()->LoadTexture(L"TearTexBlood", L"texture\\Tear\\effect_012_poof04.bmp");
	m_pBg = CResMgr::GetInst()->LoadTexture(L"ItLivesBgTex", L"texture\\Boss\\boss_78_moms guts.bmp");

	m_strAnimName = L"ITLIVES_IDLE";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"ITLIVES_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(112.f, 128.f), Vec2(112.f, 0.f), 0.0625f, 1, false);
	GetAnimator()->CreateAnimation(L"ITLIVES_BEAT", m_pTex, Vec2(0.f, 0.f), Vec2(112.f, 128.f), Vec2(112.f, 0.f), 0.0625f, 5, false);

	m_vAnimOffset = Vec2(-60.f, -48.f);

	m_arrAnimName[static_cast<UINT>(MON_STATE::IDLE)] = L"ITLIVES_IDLE";
	PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);

}

CItlives::~CItlives()
{
}

void CItlives::update()
{

	if (GetOwner()->GetOwner()->GetCurrentRoom() == GetOwner())
	{
		if (GetOwner()->GetMonsterCount() > 1)
		{
			m_bInvisible = true;
			GetCollider()->SwitchOff();
			if (!m_bMove)
			{
				m_vAnimOffset -= Vec2(0.f, 100.f);
				PlayAnim(m_pAnim, L"ITLIVES_BEAT", m_vAnimOffset, false);
				m_bMove = true;
			}
			if (GetAnimator()->GetCurAnim()->IsFinish())
			{
				GetAnimator()->GetCurAnim()->SetFrame(0);
				PlayAnim(m_pAnim, L"ITLIVES_IDLE", m_vAnimOffset, true);
			}

		}
		else
		{
			m_bInvisible = false;
			GetCollider()->SwitchOn();
			if (m_bMove)
			{
				m_vAnimOffset += Vec2(0.f, 100.f);
				PlayAnim(m_pAnim, L"ITLIVES_BEAT", m_vAnimOffset, false);
				m_bMove = false;
			}

		}

		if (!m_bRage && m_Stat.m_iHP < 500)
		{
			m_bRage = true;
			m_fAttackCooldown = 0.5f;
			m_fBeatCooldown = 0.5;
		}

		if (!m_bInvisible)
		{
			if (m_eState == ITLIVES_STATE::IDLE)
			{
				m_fAttackCooldownCount += fDT;
				m_fBeatCount += fDT;
				// idle 2초 지속시 공격
				if (m_fAttackCooldownCount >= m_fAttackCooldown)
				{
					void* p = new int();
					srand((int)p);

					int iflag = static_cast<int>(rand() % 5);
//					iflag = 4;

					if (0 == iflag)
					{
						m_eState = ITLIVES_STATE::PATTERN1;
					}
					else if (1 == iflag)
					{
						m_eState = ITLIVES_STATE::PATTERN2;
					}
					else if (2 == iflag)
					{
						m_eState = ITLIVES_STATE::PATTERN3;
					}
					else if (3 == iflag)
					{
						m_eState = ITLIVES_STATE::PATTERN4;
					}
					else if (4 == iflag)
					{
						m_eState = ITLIVES_STATE::PATTERN5;
					}
					delete p;
				}
				if (m_fBeatCount >= m_fBeatCooldown)
				{
					PlayAnim(m_pAnim, L"ITLIVES_BEAT", m_vAnimOffset, false);
				}
				else
				{
					if (GetAnimator()->GetCurAnim()->IsFinish())
					{
						PlayAnim(m_pAnim, L"ITLIVES_IDLE", m_vAnimOffset, true);
					}
				}
			}

			if (m_eState == ITLIVES_STATE::PATTERN1)
			{
				if (GetAnimator()->GetCurAnim()->IsFinish())
				{
					GetAnimator()->GetCurAnim()->SetFrame(0);
					PlayAnim(m_pAnim, L"ITLIVES_IDLE", m_vAnimOffset, true);

					CMonsterFactory::CreateMonster(MON_TYPE::Sucker, GetOwner()->GetPos() - Vec2(32.f, 0.f), GetOwner(), false);
					CMonsterFactory::CreateMonster(MON_TYPE::Sucker, GetOwner()->GetPos() + Vec2(32.f, 0.f), GetOwner(), false);
					
					m_eState = ITLIVES_STATE::IDLE;
					m_fAttackCooldownCount = 0.f;
					m_fBeatCount = 0.f;
				}
			}
			else if (m_eState == ITLIVES_STATE::PATTERN2)
			{
				m_fPattern += fDT;

				if (m_fPattern >= 0.1f)
				{
					if (!m_bTargetDefine)
					{
						vTargetDir = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetCollider()->GetFinalPos() - GetPos();
						m_bTargetDefine = true;
					}
					vTargetDir = vTargetDir.Normalize();
					for (int i = -1; i < 2; i++)
					{
						CreateMissile(vTargetDir.Rotate(20 * i), m_pTearTex, L"Itlives");
					}
					m_fPattern = 0.f;
				}
				if (GetAnimator()->GetCurAnim()->IsFinish())
				{
					if (2 != m_iPatternCount)
					{
						GetAnimator()->GetCurAnim()->SetFrame(0);
						PlayAnim(m_pAnim, L"ITLIVES_BEAT", m_vAnimOffset, false);
						++m_iPatternCount;
						return;
					}
					GetAnimator()->GetCurAnim()->SetFrame(0);
					PlayAnim(m_pAnim, L"ITLIVES_IDLE", m_vAnimOffset, true);
					m_eState = ITLIVES_STATE::IDLE;
					m_fAttackCooldownCount = 0.f;
					m_fBeatCount = 0.f;
					m_fPattern = 0.f;
					m_iPatternCount = 0;
					m_bTargetDefine = false;
				}

			}
			else if (m_eState == ITLIVES_STATE::PATTERN3)
			{
				m_fPattern += fDT;
				
				if (m_fPattern >= 0.1f)
				{
					vTargetDir = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetCollider()->GetFinalPos() - GetPos();
					vTargetDir = vTargetDir.Normalize();

					for (int i = -2; i <= 2; i++)
					{
						if (0 == i)
							continue;

						CreateMissile(vTargetDir.Rotate(20 * i), m_pTearTex, L"Itlives");
					}
					m_fPattern = 0.f;
				}
				if (GetAnimator()->GetCurAnim()->IsFinish())
				{
					if (2 != m_iPatternCount)
					{
						GetAnimator()->GetCurAnim()->SetFrame(0);
						PlayAnim(m_pAnim, L"ITLIVES_BEAT", m_vAnimOffset, false);
						++m_iPatternCount;
						return;
					}
					GetAnimator()->GetCurAnim()->SetFrame(0);
					PlayAnim(m_pAnim, L"ITLIVES_IDLE", m_vAnimOffset, true);
					m_eState = ITLIVES_STATE::IDLE;
					m_fAttackCooldownCount = 0.f;
					m_fBeatCount = 0.f;
					m_fPattern = 0.f;
					m_iPatternCount = 0;
					m_bTargetDefine = false;
				}
			}
			else if (m_eState == ITLIVES_STATE::PATTERN4)
			{
				if (GetAnimator()->GetCurAnim()->IsFinish())
				{
					GetAnimator()->GetCurAnim()->SetFrame(0);
					PlayAnim(m_pAnim, L"ITLIVES_IDLE", m_vAnimOffset, true);

					CMonsterFactory::CreateMonster(MON_TYPE::Keeper, GetOwner()->GetPos() - Vec2(400.f, 0.f) - Vec2(0.f, 150.f), GetOwner(), false);
					CMonsterFactory::CreateMonster(MON_TYPE::Keeper, GetOwner()->GetPos() + Vec2(400.f, 0.f) - Vec2(0.f, 150.f), GetOwner(), false);
					CMonsterFactory::CreateMonster(MON_TYPE::Keeper, GetOwner()->GetPos() - Vec2(400.f, 0.f) + Vec2(0.f, 150.f), GetOwner(), false);
					CMonsterFactory::CreateMonster(MON_TYPE::Keeper, GetOwner()->GetPos() + Vec2(400.f, 0.f) + Vec2(0.f, 150.f), GetOwner(), false);

					m_eState = ITLIVES_STATE::IDLE;
					m_fAttackCooldownCount = 0.f;
					m_fBeatCount = 0.f;
				}
			}
			else if (m_eState == ITLIVES_STATE::PATTERN5)
			{
			m_fPattern += fDT;

			if (m_fPattern >= 0.1f)
			{
				vTargetDir = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetCollider()->GetFinalPos() - GetPos();
				vTargetDir = vTargetDir.Normalize();
				CreateMissile(vTargetDir, m_pTearTex, L"Itlives");

				m_fPattern = 0.f;
			}
			if (GetAnimator()->GetCurAnim()->IsFinish())
			{
				if (20 != m_iPatternCount)
				{
					GetAnimator()->GetCurAnim()->SetFrame(0);
					PlayAnim(m_pAnim, L"ITLIVES_BEAT", m_vAnimOffset, false);
					++m_iPatternCount;
					return;
				}
				GetAnimator()->GetCurAnim()->SetFrame(0);
				PlayAnim(m_pAnim, L"ITLIVES_IDLE", m_vAnimOffset, true);
				m_eState = ITLIVES_STATE::IDLE;
				m_fAttackCooldownCount = 0.f;
				m_fBeatCount = 0.f;
				m_fPattern = 0.f;
				m_iPatternCount = 0;
				m_bTargetDefine = false;
			}
			}
		}

		CMonster::update();
	}
}

void CItlives::render(HDC _dc)
{
	if(CSceneMgr::GetInst()->GetCurScene()->GetMap()->GetCurrentRoom() == GetOwner())
	{
		Vec2 vScale = GetScale();
		Vec2 vPos = GetPos();
		vPos = CCamera::GetInst()->GetRenderPos(vPos);


		TransparentBlt(_dc
			, static_cast<int>(vPos.x - (vScale.x / 2) - 290)
			, static_cast<int>(vPos.y - (vScale.y / 2) - 60)
			, m_pBg->GetWidth() * 3, m_pBg->GetHeight() * 3
			, m_pBg->GetDC()
			, 0, 0, m_pBg->GetWidth(), m_pBg->GetHeight()
			, RGB(255, 0, 255));

		component_render(_dc);
	}
}

void CItlives::Attack()
{
}
