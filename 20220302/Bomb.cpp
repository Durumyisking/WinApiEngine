#include "pch.h"
#include "Bomb.h"

#include "Animation.h"
#include "ResMgr.h"
#include "Collider.h"

#include "TimeMgr.h"

CBomb::CBomb()
	: m_pTex(nullptr)
	, m_strAnimName(L"Bomb")
	, m_fBombTime(3.5f)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"Bomb	", L"texture\\Pickup\\pickup_016_bomb.bmp");
	m_pEffectTex = CResMgr::GetInst()->LoadTexture(L"Explode", L"texture\\Effect\\effect_029_explosion.bmp");

	SetName(L"Bomb");
	m_strAnimName = L"Bomb";
	SetScale(Vec2(64.f, 64.f));
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Bomb", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 1, false);
	GetAnimator()->CreateAnimation(L"Explode", m_pEffectTex, Vec2(0.f, 0.f), Vec2(96.f, 96.f), Vec2(96.f, 0.f), 0.1f, 15, false);



	CreateCollider();
	GetCollider()->SetOffsetPos(-GetScale()/2.f);
	GetCollider()->SetScale(Vec2(32.f, 32.f));

	PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), 2.f);
}

CBomb::~CBomb()
{
}

void CBomb::update()
{
	m_fBombTime -= fDT;

	if (m_fBombTime < 0)
		DeleteObject(this);



	if (m_fBombTime < 1.4f)
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"Explode";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(-48.f, -48.f), 2.f);
		GetCollider()->SetScale(Vec2(192.f, 192.f));
	}

}

void CBomb::render(HDC _dc)
{
	component_render(_dc);
}

void CBomb::OnCollision(CCollider * _pOther)
{
}

void CBomb::OnCollisionEnter(CCollider * _pOther)
{
}

void CBomb::OnCollisionExit(CCollider * _pOther)
{
}

void CBomb::CreateBomb(Vec2 _vStartPos)
{
	Vec2 vBombPos = _vStartPos; // 캐릭터의 정중앙 바닥에 설치해야함 (pos + scale/2.x, scale.y)
	vBombPos += GetScale() / 4.f;

	SetPos(vBombPos);
	SetScale(Vec2(128.f, 128.f));

	CreateObject(this, GROUP_TYPE::BOMB);
}
