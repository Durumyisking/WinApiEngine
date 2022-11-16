#include "pch.h"
#include "Fire.h"

#include "ResMgr.h"
#include "Collider.h"
#include "Texture.h"


CFire::CFire()
{
}

CFire::~CFire()
{
}

void CFire::update()
{
	m_eType = PROP_TYPE::POOP;
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PoopTex", L"texture\\Props\\grid_poop_1.bmp");
	m_iHp = 4;
	m_vScale = { 32.f, 32.f };
	SetScale(Vec2(70.f, 70.f));
	CreateCollider();
	GetCollider()->SetScale(Vec2(70.f, 70.f));
}

void CFire::render(HDC _dc)
{
	if (m_iHp == 0)
	{
		GetCollider()->SwitchOff();
	}

}

void CFire::OnCollision(CCollider* _pOther)
{
}

void CFire::OnCollisionEnter(CCollider* _pOther)
{
}
