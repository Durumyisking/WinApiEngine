#include "pch.h"
#include "Monster.h"
#include "Missile.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "Camera.h"



CMonster::CMonster()
	: m_Stat{}
	, m_pAnim(nullptr)
	, m_iDir(1)
	, m_fAcc(0.f)
	, m_pTex(nullptr)

{
	SetName(L"Monster");
	CreateCollider();
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
}


void CMonster::render(HDC _dc)
{

	component_render(_dc);
}
void CMonster::OnCollision(CCollider * _pOther)
{
	//CObject* pOtherObj = _pOther->GetObj();

//// player 
//if (L"Player" == pOtherObj->GetName())
//{
//	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pOtherObj);
//	
//	pPlayer->SetPrevHp(pPlayer->GetStat()->m_iHP);
//	GetStat().InflictDamage(pPlayer->GetStat());
//}
}
void CMonster::OnCollisionEnter(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (L"Tear_Player" == pOtherObj->GetName())
	{
		CMissile* pMissileObj = dynamic_cast<CMissile*>(pOtherObj);

		m_Stat.m_iHP -= pMissileObj->GetDmg();

		if (0 >= m_Stat.m_iHP)
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