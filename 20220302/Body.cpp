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
	:  m_strAnimName(L"BODY_IDLE")
	, m_fAnimFrame(0.05f)

{

	SetScale(Vec2(54.f, 39.f));

	// isaac body
	CTexture* m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player\\isaac.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"BODY_IDLE", m_pTex, Vec2(15.f, 80.f), Vec2(18.f, 15.f), Vec2(32.f, 0.f), 0.5f, 1, false);

	GetAnimator()->CreateAnimation(L"BODY_UP", m_pTex, Vec2(15.f, 80.f), Vec2(18.f, 15.f), Vec2(32.f, 0.f), 0.05f, 5, false);
	GetAnimator()->CreateAnimation(L"BODY_DOWN", m_pTex, Vec2(175.f, 80.f), Vec2(18.f, 15.f), Vec2(32.f, 0.f), 0.05f, 5, false);
	GetAnimator()->CreateAnimation(L"BODY_LEFT", m_pTex, Vec2(15.f, 154.f), Vec2(19.f, 14.f), Vec2(32.f, 0.f), 0.05f, 10, false);
	GetAnimator()->CreateAnimation(L"BODY_RIGHT", m_pTex, Vec2(15.f, 123.f), Vec2(18.f, 14.f), Vec2(32.f, 0.f), 0.05f, 10, false);
	


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


