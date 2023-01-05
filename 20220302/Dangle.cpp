#include "pch.h"
#include "Dangle.h"
#include "Missile.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "RigidBody.h"

CDangle::CDangle()
	: m_fAttackCooldown(0.f)
	, m_fAttackPrePare(0.f)
	, m_fPostTimer(0.f)
	, m_eState(DANGLE_STATE::IDLE)
	, m_bAnimPlaying(false)
	, m_pTearTex(nullptr)
	, m_iChargeCount(0)
	, m_vTargetDir()
	, m_fChargeForce(0.f)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"DangleTex", L"texture\\Boss\\boss_085_dangle.bmp");
	m_pTearTex = CResMgr::GetInst()->LoadTexture(L"TearTexCorn", L"texture\\Tear\\effect_999_cornpoofa.bmp");
	m_strAnimName = L"DANGLE_IDLE";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"DANGLE_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 3, false);
	GetAnimator()->CreateAnimation(L"DANGLE_BEFOREATTACK", m_pTex, Vec2(192.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 4, false); // prepare���� �ݵ�� ����
	GetAnimator()->CreateAnimation(L"DANGLE_ATTACK_PREPARE1", m_pTex, Vec2(0.f, 256.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 6, false);
	GetAnimator()->CreateAnimation(L"DANGLE_ATTACK_PREPARE2", m_pTex, Vec2(192.f, 128.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 3, false);
	GetAnimator()->CreateAnimation(L"DANGLE_ATTACK1", m_pTex, Vec2(0.f, 192.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 3, false);
	GetAnimator()->CreateAnimation(L"DANGLE_ATTACK1_POST", m_pTex, Vec2(384.f, 64.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 2, false); // ATTACK!�̳����� �̰� ����ϰ� �����

	GetAnimator()->CreateAnimation(L"DANGLE_CHARGE_PREPARE", m_pTex, Vec2(384.f, 128.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.15f, 2, false); // ���� �غ�
	GetAnimator()->CreateAnimation(L"DANGLE_CHARGE", m_pTex, Vec2(0.f, 64.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 8, false); // ����
	GetAnimator()->CreateAnimation(L"DANGLE_STUN", m_pTex, Vec2(192.f, 192.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.5f, 2, false); // ���������� ����

	GetAnimator()->CreateAnimation(L"DANGLE_DEAD", m_pTex, Vec2(0.f, 320.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 15, false);


	m_arrAnimName[static_cast<UINT>(MON_STATE::IDLE)] = L"DANGLE_IDLE";
	m_arrAnimName[static_cast<UINT>(MON_STATE::DEAD)] = L"DANGLE_DEAD";


	PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);
	m_bAnimPlaying = true;
	m_bDeadAnim = false;
}

CDangle::~CDangle()
{
}

void CDangle::update()
{
	if (GetOwner()->GetOwner()->GetCurrentRoom() == GetOwner())
	{
		CMonster::update();

		if (0 < m_Stat.m_iHP)
		{

			if (m_eState == DANGLE_STATE::IDLE)
			{
				m_fAttackCooldown += fDT;

				// idle 2�� ���ӽ� ����
				if (m_fAttackCooldown > 2.f)
				{
					m_eState = DANGLE_STATE::BEFOREATTACK;
					m_bAnimPlaying = false;
					m_fAttackCooldown = 0.f;

				}
			}

			if (m_eState == DANGLE_STATE::BEFOREATTACK)
			{
				// ó�� ��������
				if (!m_bAnimPlaying)
				{
					m_strAnimName = L"DANGLE_BEFOREATTACK";
					PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), false);
					m_bAnimPlaying = true;
				}

				// �ִϸ��̼� ������ ATTACKPRE��
				if (GetAnimator()->GetCurAnim()->IsFinish())
				{
					GetAnimator()->GetCurAnim()->SetFrame(0);
					srand(CTimeMgr::GetInst()->GetCurCount() * CTimeMgr::GetInst()->GetCurCount());
					int iflag1 = static_cast<int>(rand() % 2);
					if (0 == iflag1) // attack �б�
					{
						srand(CTimeMgr::GetInst()->GetCurCount());
						int iflag2 = static_cast<int>(rand() % 2);
						if (0 == iflag2)
						{
							m_strAnimName = L"DANGLE_ATTACK_PREPARE1";
							m_eState = DANGLE_STATE::ATTACKPRE1;
							PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);
						}
						else
						{
							m_strAnimName = L"DANGLE_ATTACK_PREPARE2";
							m_eState = DANGLE_STATE::ATTACKPRE2;
							PlayAnim(m_pAnim, m_strAnimName, Vec2(-17.f, 0.f), true);
						}
					}
					else // charge �б�
					{
						m_eState = DANGLE_STATE::CHARGEPRE;
						m_bAnimPlaying = false;
					}
				}
			}

			/////////////////////////////////////// 
			/////////////ATTACK �б�///////////////
			/////////////////////////////////////// 
			if (m_eState == DANGLE_STATE::ATTACKPRE1
				|| m_eState == DANGLE_STATE::ATTACKPRE2)
			{
				m_fAttackPrePare += fDT;

				// 1�ʰ� ���� �غ�
				if (m_fAttackPrePare > 1.f)
				{
					m_eState = DANGLE_STATE::ATTACK;
					m_bAnimPlaying = false;
					m_fAttackPrePare = 0.f;
				}
			}

			if (m_eState == DANGLE_STATE::ATTACK)
			{
				// ó�� ��������
				if (!m_bAnimPlaying)
				{
					m_strAnimName = L"DANGLE_ATTACK1";
					PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), false);
					m_bAnimPlaying = true;
					Attack();
				}

				// �ִϸ��̼� ������ ATTACKPOST��
				if (GetAnimator()->GetCurAnim()->IsFinish())
				{
					CMonsterFactory::CreateMonster(MON_TYPE::Sucker, GetPos(), GetOwner(), false);

					GetAnimator()->GetCurAnim()->SetFrame(0);
					m_strAnimName = L"DANGLE_ATTACK1_POST";
					m_eState = DANGLE_STATE::ATTACKPOST;
					PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);
				}

			}

			if (m_eState == DANGLE_STATE::ATTACKPOST)
			{
				m_fPostTimer += fDT;

				// 1�ʰ� ���� �غ�
				if (m_fPostTimer > 0.5f)
				{
					m_eState = DANGLE_STATE::IDLE;
					m_strAnimName = L"DANGLE_IDLE";
					PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);
					m_fPostTimer = 0.f;
				}
			}

			/////////////////////////////////////// 
			/////////////Charge �б�///////////////
			/////////////////////////////////////// 
			if (m_eState == DANGLE_STATE::CHARGEPRE)
			{
				if (!m_bAnimPlaying)
				{
					m_strAnimName = L"DANGLE_CHARGE_PREPARE";
					m_eState = DANGLE_STATE::CHARGEPRE;
					PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), false);
					m_bAnimPlaying = true;
				}

				// �ִϸ��̼� ������ CHARGE��
				if (GetAnimator()->GetCurAnim()->IsFinish())
				{
					GetAnimator()->GetCurAnim()->SetFrame(0);
					m_eState = DANGLE_STATE::CHARGE;
					m_bAnimPlaying = false;
				}
			}

			if (m_eState == DANGLE_STATE::CHARGE)
			{
				// ó�� ��������
				if (!m_bAnimPlaying)
				{
					m_strAnimName = L"DANGLE_CHARGE";
					PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), false);
					m_bAnimPlaying = true;
					//follow player
					m_vTargetDir = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetPos() - GetPos();
					m_vTargetDir += Vec2(0.f, 45.f);
					m_vTargetDir.Normalize();
					m_fChargeForce = 0.f;
					++m_iChargeCount;
				}

				Charge();

				// �ִϸ��̼� ������ ATTACKPOST��
				if (GetAnimator()->GetCurAnim()->IsFinish())
				{
					GetAnimator()->GetCurAnim()->SetFrame(0);
					if (2 == m_iChargeCount)
					{
						m_iChargeCount = 0;
						m_strAnimName = L"DANGLE_STUN";
						m_eState = DANGLE_STATE::STUN;
						PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);
					}
					else
					{
						m_eState = DANGLE_STATE::CHARGEPRE;
						m_bAnimPlaying = false;
					}
				}

			}

			if (m_eState == DANGLE_STATE::STUN)
			{
				m_fPostTimer += fDT;

				// 1�ʰ� ���� �غ�
				if (m_fPostTimer > 2.f)
				{
					m_eState = DANGLE_STATE::IDLE;
					m_strAnimName = L"DANGLE_IDLE";
					PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);
					m_fPostTimer = 0.f;
				}
			}
		}
	}
}

void CDangle::Attack()
{
	Vec2 vTargetDir = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetCollider()->GetFinalPos() - GetPos();

	vTargetDir = vTargetDir.Normalize();
	for (int i = -1; i < 2; i++)
	{
		CreateMissile(vTargetDir.Rotate(20 * i), m_pTearTex, L"Dangle");
	}
}

void CDangle::OnCollision(CCollider* _pOther)
{
	CMonster::OnCollision(_pOther);
}

void CDangle::OnCollisionEnter(CCollider* _pOther)
{
	CMonster::OnCollisionEnter(_pOther);
}

void CDangle::OnCollisionExit(CCollider* _pOther)
{
	CMonster::OnCollisionExit(_pOther);
}



void CDangle::Charge()
{
	m_vTargetDir.Normalize();

	m_fChargeForce += 100.f * fDT;
	m_vTargetDir *= m_fChargeForce;
	CRigidBody* pRigid = GetRigidBody();
	pRigid->AddVelocity(m_vTargetDir);

}
