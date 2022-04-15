#include "pch.h"
#include "Monster.h"
#include "Missile.h"
#include"Collider.h"

#include "TimeMgr.h"
#include "ResMgr.h"
#include "Camera.h"




CMonster::CMonster()
	: m_vCenterPos(Vec2(640.f, 150.f))
	, m_fSpeed(0.f)
	, m_fMaxDistance(0.f)
	, m_iDir(1)
	, m_fAcc(0.f)
	, m_dPrevTime(fDT)
	, m_pTex(nullptr)
	, m_iHP(5)


{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"MonsterTex", L"texture\\Monster\\Monster_1.bmp");
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(30.f, 30.f));
}


CMonster::~CMonster()
{

}

void CMonster::Attack(MISSILE_TYPE _eType)
{
	CMissile* pMissile = new CMissile;
	pMissile->CreateMissile(_eType, GetPos(), GROUP_TYPE::PROJ_MONSTER);
}


void CMonster::update()
{
	m_dPrevTime += fDT;

	Vec2 vCurPos = GetPos();

	m_fSpeed = m_fSpeed + m_iDir * fDT * m_fAcc;
	vCurPos.y = vCurPos.y + m_fSpeed * fDT;

	// 설정해준 최대 이동거리를 넘어서 이동했을때
	/*float fDist = abs(m_vCenterPos.y - vCurPos.y) - m_fMaxDistance;

	if (0.f < fDist)
	{
		m_iDir *= 0;
		vCurPos.y += fDist * m_iDir;
	}*/

	//if (m_fMaxDistance - vCurPos.y <= 500.f)
	//{
	//	m_fAcc = -300.f;
	//}
	/*if (vCurPos.y >= m_fMaxDistance)
	{
		m_fSpeed = 0.f;
		m_iDir = 0;
		m_fAcc = 0.f;
	}*/
	if (m_fSpeed <= 0)
	{
		m_fSpeed = 0.f;
		m_iDir = 0;
		m_fAcc = 0.f;

		if (0.f > 1.f - m_dPrevTime)
		{		
			Attack(MISSILE_TYPE::DEFAULT);
			m_dPrevTime = 0.f;
		}
	}



	SetPos(vCurPos);
}

void CMonster::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height(); 

	Vec2 vPos = GetPos();

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(vPos);
	
	TransparentBlt(_dc
		, (int)(vRenderPos.x - (float)(iWidth / 2))
		, (int)(vRenderPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	component_render(_dc);
}

void CMonster::OnCollision(CCollider * _pOther)
{
	
}

void CMonster::OnCollisionEnter(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (L"Missile_Player" == pOtherObj->GetName())
	{
		--m_iHP;

		if(0 >= m_iHP)
			DeleteObject(this);
	}
}

void CMonster::OnCollisionExit(CCollider * _pOther)
{

}
