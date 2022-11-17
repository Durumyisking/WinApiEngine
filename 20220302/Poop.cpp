#include "pch.h"
#include "Poop.h"

#include "ResMgr.h"
#include "Collider.h"
#include "Texture.h"


CPoop::CPoop()
	
{
	SetName(L"Poop");
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
	Vec2 vScale = GetScale();
	Vec2 vPos = GetPos();

	// 카메라 시점 동기화
	vPos = CCamera::GetInst()->GetRenderPos(vPos);


	// 렌더링 오프셋 적용
	TransparentBlt(_dc
		, static_cast<int>(vPos.x - (vScale.x / 2.f))
		, static_cast<int>(vPos.y - (vScale.y / 2.f))
		, static_cast<int>(vScale.x), static_cast<int>(vScale.y)
		, m_pTex->GetDC()
		, m_vSlice.x * m_vScale.x, m_vSlice.y * m_vScale.y, m_vScale.x, m_vScale.y
		, RGB(255, 0, 255));

	component_render(_dc);
}

void CPoop::OnCollision(CCollider* _pOther)
{
}

void CPoop::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (L"Tear_Player" == pOtherObj->GetName())
	{
		--m_iHp;
		m_vSlice += {1.f, 0.f};
	}
}
