#include "pch.h"
#include "Monster.h"
#include "Missile.h"
#include"Collider.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "Camera.h"
#include "AI.h"



CMonster::CMonster()
	: stat{ 30, 30, 1, 400.f, 0.38f }
	, m_pAnim(nullptr)
	, m_iDir(1)
	, m_fAcc(0.f)

{
	SetName(L"Monster");
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(30.f, 30.f));
}
CMonster::~CMonster()
{
	if (nullptr != m_pAI)
	{
		delete m_pAI;
	}
}


void CMonster::Attack(MISSILE_TYPE _eType)
{


}


void CMonster::update()
{
	m_pAI->update();
	
	Vec2 vCurPos = GetPos();


	SetPos(vCurPos);
}

void CMonster::render(HDC _dc)
{
	/*int iWidth = (int)m_pTex->GetWidth();
	int iHeight = (int)m_pTex->GetHeight();

	Vec2 vPos = GetPos();
		
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_dc
		, (int)(vRenderPos.x - (float)(iWidth / 2))
		, (int)(vRenderPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));*/
	component_render(_dc);
}
void CMonster::OnCollision(CCollider * _pOther)
{

}
void CMonster::OnCollisionEnter(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (L"Tear_Player" == pOtherObj->GetName())
	{
		CMissile* pMissileObj = dynamic_cast<CMissile*>(pOtherObj);

		stat.m_iHP -= pMissileObj->GetDmg();

		if (0 >= stat.m_iHP)
			DeleteObject(this);
	}
}
void CMonster::OnCollisionExit(CCollider * _pOther)
{
}

void CMonster::SetAI(CAI * _pAI)
{
	m_pAI = _pAI;
	m_pAI->m_pOwner = this;
}