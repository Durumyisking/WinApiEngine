#include "pch.h"
#include "Props.h"

#include "ResMgr.h"
#include "Collider.h"
#include "Texture.h"

CProps::CProps()
	:m_pTex(nullptr)
	, m_iHp(0)
	, m_eType(PROP_TYPE::END)
	, m_vSlice(0.f, 0.f)
	, m_vScale(0.f, 0.f)
	, m_IsRock(false)
{
	SetName(L"Prop");

}


CProps::~CProps()
{
}

void CProps::update()
{
}

void CProps::render(HDC _dc)
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

void CProps::OnCollision(CCollider* _pOther)
{
}

void CProps::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	
	if (L"Tear_Player" == pOtherObj->GetName())
	{
		--m_iHp;
		m_vSlice += {1.f, 0.f};
	}


}
