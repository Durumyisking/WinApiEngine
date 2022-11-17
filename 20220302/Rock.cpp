#include "pch.h"
#include "Rock.h"


#include "ResMgr.h"
#include "Collider.h"
#include "Texture.h"

CRock::CRock()
	: m_bCracked(false)
	, m_vSlice{}
{
	SetName(L"Rock");
	m_pTex = CResMgr::GetInst()->LoadTexture(L"RockTex", L"texture\\Props\\Rock.bmp");

	m_vScale = { 32.f, 32.f };

	void* p = new int();
	srand((int)p);

	int iType = rand() % 2;

	switch (iType)
	{
	case 0:
		m_vSlice = { 0.f, 0.f };
		break;
	case 1:
		m_vSlice = { 1.f, 0.f };
		break;
	case 2:
		m_vSlice = { 2.f, 0.f };
		break;
	default:
		break;
	}
	delete p;


	SetScale(Vec2(90.f, 90.f));
	CreateCollider();
	GetCollider()->SetScale(Vec2(70.f, 70.f));

}

CRock::~CRock()
{
}

void CRock::update()
{
	if (m_bCracked)
	{
		GetCollider()->SwitchOff();
	}

}

void CRock::render(HDC _dc)
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


void CRock::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Explode" == pOtherObj->GetName())
	{
		m_vSlice = { 4.f, 0.f };

		GetCollider()->SwitchOff();
	}
}

void CRock::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (L"Explode" == pOtherObj->GetName())
	{
		m_vSlice = { 4.f, 0.f };

		GetCollider()->SwitchOff();
	}

}
