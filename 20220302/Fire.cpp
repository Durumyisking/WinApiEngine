#include "pch.h"
#include "Fire.h"

#include "ResMgr.h"
#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "Room.h"

CFire::CFire()
{
	SetName(L"Fire");
	m_pTex = CResMgr::GetInst()->LoadTexture(L"FireTex", L"texture\\Props\\grid_fireplace_r.bmp");
	m_iHp = 4;

	SetScale(Vec2(70.f, 70.f));
	CreateCollider();
	GetCollider()->SetScale(Vec2(70.f, 70.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"FirePlace_IDLE", m_pTex, Vec2(32.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 6, false);
	GetAnimator()->CreateAnimation(L"FirePlace_DEAD", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 1, false);

	PlayAnim(m_pAnim, L"FirePlace_IDLE", Vec2(0.f, 0.f), true);
	GetAnimator()->GetCurAnim()->SetOffset({ -8.f, -8.f });

}

CFire::~CFire()
{
}

void CFire::update()
{
}

void CFire::render(HDC _dc)
{
	if (nullptr == GetOwner())
		return;
	if (GetOwner()->GetOwner()->GetCurrentRoom() == GetOwner() || GetOwner()->GetOwner()->GetPrevRoom() == GetOwner())
	{
		component_render(_dc);
	}
}

void CFire::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Explode" == pOtherObj->GetName())
	{
		m_iHp = 0;
	}
	if (m_iHp == 0)
	{
		GetCollider()->SwitchOff();
		PlayAnim(m_pAnim, L"FirePlace_DEAD", Vec2(0.f, 0.f), true);
		GetAnimator()->GetCurAnim()->SetOffset({ -8.f, -8.f });
	}
}

void CFire::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (L"Tear_Player" == pOtherObj->GetName())
	{
		--m_iHp;
	}
	if (L"Explode" == pOtherObj->GetName())
	{
		m_iHp = 0;
	}

	if (m_iHp == 0)
	{
		GetCollider()->SwitchOff();
		PlayAnim(m_pAnim, L"FirePlace_DEAD", Vec2(0.f, 0.f), true);
		GetAnimator()->GetCurAnim()->SetOffset({ -8.f, -8.f });
	}



}
