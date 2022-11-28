#include "pch.h"

#include "Costume.h"
#include "Animation.h"
#include "Animator.h"
#include "ResMgr.h"
#include "KeyMgr.h"

CCostume::CCostume(ITEM_TABLE _eItem)
	: m_pPlayer(nullptr)
	, m_pTex(nullptr)
	, m_eItemName(_eItem)
	, m_bIsHead(false)
	, m_bHaveUp(false)
	, m_pAnim(nullptr)
{
	CreateAnimator();

	switch (m_eItemName)
	{
	case ITEM_TABLE::sadonion:
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"sadonion_cos", L"texture\\Costume\\costume_058_sadonion.bmp");
		m_strAnimName = L"sadonion_IDLE";
		SetName(L"sadonion");
		m_vAnimOffset = Vec2(-64.f, -64.f);
		m_bIsHead = true;
		GetAnimator()->CreateAnimation(L"sadonion_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.05f, 3, false);
		GetAnimator()->CreateAnimation(L"sadonion_UPDOWN", m_pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.05f, 3, false);
		GetAnimator()->CreateAnimation(L"sadonion_LEFT", m_pTex, Vec2(0.f, 64.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.05f, 3, false);
		GetAnimator()->CreateAnimation(L"sadonion_RIGHT", m_pTex, Vec2(0.f, 128.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.05f, 3, false);

	}
		break;
	case ITEM_TABLE::belt:
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"belt_cos", L"texture\\Costume\\costume_015_belt.bmp");
		m_strAnimName = L"belt_IDLE";
		SetName(L"belt");
		m_vAnimOffset = Vec2(-32.f, 0.f);
		GetAnimator()->CreateAnimation(L"belt_IDLE", m_pTex, Vec2(0.f, 32.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 1, false);
		GetAnimator()->CreateAnimation(L"belt_UPDOWN", m_pTex, Vec2(0.f, 32.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 10, false);
		GetAnimator()->CreateAnimation(L"belt_LEFT", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 10, false);
		GetAnimator()->CreateAnimation(L"belt_RIGHT", m_pTex, Vec2(0.f, 64.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 10, false);

	}
		break;
	case ITEM_TABLE::momsheels:
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"momsheels_cos", L"texture\\Costume\\costume_041_momsheels.bmp");
		m_strAnimName = L"momsheels_IDLE";
		SetName(L"momsheels");
		m_vAnimOffset = Vec2(-32.f, 0.f);
		GetAnimator()->CreateAnimation(L"momsheels_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 1, false);
		GetAnimator()->CreateAnimation(L"momsheels_UPDOWN", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 10, false);
		GetAnimator()->CreateAnimation(L"momsheels_LEFT", m_pTex, Vec2(0.f, 32.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 10, false);
		GetAnimator()->CreateAnimation(L"momsheels_RIGHT", m_pTex, Vec2(0.f, 64.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 10, false);

	}
		break;
	//case ITEM_TABLE::sagittarius:
	//{
	//	m_pTex = CResMgr::GetInst()->LoadTexture(L"sagittarius_cos", L"texture\\Costume\\costume_306_sagittarius.bmp");
	//	m_strAnimName = L"sagittarius_IDLE";
	//	SetName(L"sagittarius");
	//	m_vAnimOffset = Vec2(-32.f, 0.f);
	//	GetAnimator()->CreateAnimation(L"sagittarius_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 1, false);
	//	GetAnimator()->CreateAnimation(L"sagittarius_UPDOWN", m_pTex, Vec2(0.f, 64.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 10, false);
	//	GetAnimator()->CreateAnimation(L"sagittarius_RIGHT", m_pTex, Vec2(288.f, 32.f), Vec2(32.f, 32.f), Vec2(-32.f, 0.f), 0.05f, 10, false);
	//	GetAnimator()->CreateAnimation(L"sagittarius_LEFT", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 10, false);

	//}
	//break;

	//case ITEM_TABLE::mrmega:
	//{
	//	m_pTex = CResMgr::GetInst()->LoadTexture(L"mrmega_cos", L"texture\\Costume\\costume_046_mrmega.bmp");
	//	m_strAnimName = L"mrmega_IDLE";
	//	SetName(L"mrmega");
	//	m_bIsHead = true;
	//	m_bHaveUp = true;
	//	m_vAnimOffset = Vec2(-32.f, -64.f);
	//	GetAnimator()->CreateAnimation(L"mrmega_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 64.f), Vec2(32.f, 0.f), 0.5f, 1, false);
	//	GetAnimator()->CreateAnimation(L"mrmega_UP", m_pTex, Vec2(128.f, 0.f), Vec2(32.f, 64.f), Vec2(32.f, 0.f), 0.5f, 2, false);
	//	GetAnimator()->CreateAnimation(L"mrmega_DOWN", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 64.f), Vec2(32.f, 0.f), 0.5f, 2, false);
	//	GetAnimator()->CreateAnimation(L"mrmega_LEFT", m_pTex, Vec2(192.f, 32.f), Vec2(32.f, 64.f), Vec2(32.f, 0.f), 0.5f, 2, false);
	//	GetAnimator()->CreateAnimation(L"mrmega_RIGHT", m_pTex, Vec2(64.f, 64.f), Vec2(32.f, 64.f), Vec2(32.f, 0.f), 0.5f, 2, false);

	//}
	//break;
	//
	//case ITEM_TABLE::polyphemus:
	//{
	//	m_pTex = CResMgr::GetInst()->LoadTexture(L"polyphemus_cos", L"texture\\Costume\\costume_106_polyphemus.bmp");
	//	m_strAnimName = L"polyphemus_IDLE";
	//	SetName(L"polyphemus");
	//	m_bIsHead = true;
	//	m_bHaveUp = true;
	//	m_vAnimOffset = Vec2(-32.f, -64.f);
	//	GetAnimator()->CreateAnimation(L"polyphemus_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 64.f), Vec2(32.f, 0.f), 0.5f, 1, false);
	//	GetAnimator()->CreateAnimation(L"polyphemus_UP", m_pTex, Vec2(128.f, 0.f), Vec2(32.f, 64.f), Vec2(32.f, 0.f), 0.5f, 2, false);
	//	GetAnimator()->CreateAnimation(L"polyphemus_DOWN", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 64.f), Vec2(32.f, 0.f), 0.5f, 2, false);
	//	GetAnimator()->CreateAnimation(L"polyphemus_LEFT", m_pTex, Vec2(192.f, 32.f), Vec2(32.f, 64.f), Vec2(32.f, 0.f), 0.5f, 2, false);
	//	GetAnimator()->CreateAnimation(L"polyphemus_RIGHT", m_pTex, Vec2(64.f, 64.f), Vec2(32.f, 64.f), Vec2(32.f, 0.f), 0.5f, 2, false);

	//}
	//break;

	case ITEM_TABLE::normalend:
		break; 
		default:
			m_eItemName = ITEM_TABLE::normalend;
			break;
	}
}


CCostume::~CCostume()
{

}

void CCostume::update()
{
	if (nullptr != m_pPlayer)
	{ 
		SetPos(m_pPlayer->GetPos());

			if(m_bHaveUp)
			{
				if (KEY_HOLD(KEY::W))
				{
					m_strAnimName = GetName() + L"_UP";
					PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
				}
				if (KEY_HOLD(KEY::S))
				{
					m_strAnimName = GetName() + L"_DOWN";
					PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
				}
			}
			else
			{
				if (KEY_HOLD(KEY::W) || KEY_HOLD(KEY::S))
				{
					m_strAnimName = GetName() + L"_UPDOWN";
					PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
				}
			}
			if (KEY_HOLD(KEY::A))
			{
				m_strAnimName = GetName() + L"_RIGHT";
				PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
			}
			if (KEY_HOLD(KEY::D))
			{
				m_strAnimName = GetName() + L"_LEFT";
				PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
			}


			// 머리에 달린 애니메이션

			if (m_bIsHead)
			{
				if (KEY_HOLD(KEY::UP) || KEY_HOLD(KEY::DOWN))
				{
					m_strAnimName = GetName() + L"_UPDOWN";
					PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);

				}
				if (KEY_HOLD(KEY::RIGHT))
				{
					m_strAnimName = GetName() + L"_LEFT";
					PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
				}
				if (KEY_HOLD(KEY::LEFT))
				{
					m_strAnimName = GetName() + L"_RIGHT";
					PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
				}
			}

			if (KEY_AWAY(KEY::UP) || KEY_AWAY(KEY::DOWN) ||
				KEY_AWAY(KEY::LEFT) || KEY_AWAY(KEY::RIGHT) ||
				KEY_AWAY(KEY::W) || KEY_AWAY(KEY::S) ||
				KEY_AWAY(KEY::A) || KEY_AWAY(KEY::D))
			{
				m_strAnimName = GetName() + L"_IDLE";
				PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
			}
		

	}
}

