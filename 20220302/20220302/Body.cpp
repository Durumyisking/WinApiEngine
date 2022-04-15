#include "pch.h"
#include "Body.h"
#include "Head.h"

#include "Collider.h"
#include "Animation.h"
#include "Animator.h"

#include "ResMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"

CBody::CBody()
	: m_pAnim(nullptr)
	, m_strAnimName(L"BODY_IDLE")

{

	CreateCollider();
	GetCollider()->SetOffsetPos(HEAD_BODY_GAP);
	GetCollider()->SetScale(BODY_DEFAULT);
	SetScale(BODY_DEFAULT);

	// isaac body
	CTexture* m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player\\isaaac.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"BODY_IDLE", m_pTex, Vec2(15.f, 80.f), Vec2(18.f, 15.f), Vec2(32.f, 0.f), 0.5f, 1);

	GetAnimator()->CreateAnimation(L"BODY_UP", m_pTex, Vec2(15.f, 80.f), Vec2(18.f, 15.f), Vec2(32.f, 0.f), 0.05f, 5);
	GetAnimator()->CreateAnimation(L"BODY_DOWN", m_pTex, Vec2(175.f, 80.f), Vec2(18.f, 15.f), Vec2(32.f, 0.f), 0.05f, 5);
	GetAnimator()->CreateAnimation(L"BODY_LEFT", m_pTex, Vec2(15.f, 123.f), Vec2(18.f, 13.f), Vec2(32.f, 0.f), 0.05f, 5);
	GetAnimator()->CreateAnimation(L"BODY_RIGHT", m_pTex, Vec2(15.f, 123.f), Vec2(18.f, 13.f), Vec2(32.f, 0.f), 0.05f, 10);
	


	PlayAnim(m_pAnim, m_strAnimName, HEAD_BODY_GAP);
}


CBody::~CBody()
{
}

void CBody::update()
{
	CPlayer::update();

	if (KEY_HOLD(KEY::W))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"BODY_UP";
		PlayAnim(m_pAnim, m_strAnimName, HEAD_BODY_GAP);


	}
	if (KEY_HOLD(KEY::S))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"BODY_DOWN";
		PlayAnim(m_pAnim, m_strAnimName, HEAD_BODY_GAP);
	}
	if (KEY_HOLD(KEY::A))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"BODY_LEFT";
		PlayAnim(m_pAnim, m_strAnimName, HEAD_BODY_GAP);
	}
	if (KEY_HOLD(KEY::D))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"BODY_RIGHT";
		PlayAnim(m_pAnim, m_strAnimName, HEAD_BODY_GAP);
	}

	if (KEY_AWAY(KEY::W) || KEY_AWAY(KEY::S) ||
		KEY_AWAY(KEY::A) || KEY_AWAY(KEY::D))
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"BODY_IDLE";
		PlayAnim(m_pAnim, m_strAnimName, HEAD_BODY_GAP);
	}

}


