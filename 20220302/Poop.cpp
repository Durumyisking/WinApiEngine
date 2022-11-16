#include "pch.h"
#include "Poop.h"

#include "ResMgr.h"
#include "Collider.h"
#include "Texture.h"


CPoop::CPoop()
	
{
	m_eType = PROP_TYPE::POOP;
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PoopTex", L"texture\\Props\\grid_poop_1.bmp");
	m_iHp = 4;
	m_vScale = { 32.f, 32.f };
	SetScale(Vec2(70.f, 70.f));
	CreateCollider();
	GetCollider()->SetScale(Vec2(70.f, 70.f));

}


CPoop::~CPoop()
{

}

void CPoop::update()
{
	if (m_iHp == 0)
	{
		GetCollider()->SwitchOff();
	}
}

void CPoop::render(HDC _dc)
{
	CProps::render(_dc);
}

void CPoop::OnCollision(CCollider* _pOther)
{
	CProps::OnCollision(_pOther);
}

void CPoop::OnCollisionEnter(CCollider* _pOther)
{
	CProps::OnCollisionEnter(_pOther);
}
