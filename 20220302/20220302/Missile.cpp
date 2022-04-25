#include "pch.h"
#include "Missile.h"
#include "Core.h"
#include "Player.h"
#include "Monster.h"
#include "Scene.h"
#include"Collider.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "ResMgr.h"
#include "Camera.h"
#include "Core.h"
CMissile::CMissile()
	: m_fTheta(PI / 2.f)
	, m_vDir(Vec2(0.f, -1.f))
	, m_vStartvec(Vec2(0.f, 0.f))
	, m_eType(MISSILE_TYPE::DEFAULT)
	, m_fModifyXDir(0.1f)
	, m_fModifyYDir(0.f)
	, m_fSpeedx(0.f)
	, m_fSpeedy(0.f)
	, m_bCase(false)
	, m_pTex(nullptr)
{
	m_vDir.Normalize();

	CreateCollider();
	GetCollider()->SetOffsetPos(TEAR_DEFAULT);
	GetCollider()->SetScale(TEAR_DEFAULT);
	SetScale(TEAR_DEFAULT);
}
CMissile::~CMissile()
{
}
void CMissile::update()
{
	Vec2 vPos = GetPos();

	switch (m_eType)
	{
	case MISSILE_TYPE::DEFAULT:
	{
		m_fSpeedx = 300.f;
		m_fSpeedy = 300.f;
		vPos.x += m_fSpeedx * m_vDir.x * fDT;
		vPos.y += m_fSpeedy * m_vDir.y * fDT;
		SetPos(vPos);
	}
	break;

	default:
		break;
	}
	if (0 > GetPos().y)
	{
		// scene의 obj벡터의 여기 인덱스를 erase 해주는 함수
		

		// delete this;
	}
}
void CMissile::render(HDC _dc)
{

	int iWidth = (int)m_pTex->GetWidth();
	int iHeight = (int)m_pTex->GetHeight();


	Vec2 vPos = GetPos();


	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(vPos);
	TransparentBlt(_dc
		, (int)(vRenderPos.x)
		, (int)(vRenderPos.y)
		, GetScale().x * 2, GetScale().y * 2
		, m_pTex->GetDC()
		, 0, iHeight/4, iWidth/8, iHeight/4
		, RGB(255, 0, 255));
	component_render(_dc);
}
void CMissile::CreateMissile(MISSILE_TYPE _eType, Vec2 _vStartPos, GROUP_TYPE _eShooter)
{
	Vec2 vMissilePos = _vStartPos; // 현재 플레이어의 위치 가져옴
	vMissilePos.y -= GetScale().y / 2.f;

	SetPos(vMissilePos);
	SetStartVec(Vec2(vMissilePos));
	SetScale(TEAR_DEFAULT);

	switch (_eType)
	{
	case MISSILE_TYPE::DEFAULT:
		SetType(MISSILE_TYPE::DEFAULT);
		m_pTex = CResMgr::GetInst()->LoadTexture(L"Tear_Tex", L"texture\\Tear\\tears.bmp");
		if (GROUP_TYPE::PROJ_PLAYER == _eShooter)
		{

			SetName(L"Missile_Player");
		}

		else if (GROUP_TYPE::PROJ_MONSTER == _eShooter)
		{
			SetName(L"Missile_Monster");
		}
		break;

	default:
		break;
	}
	CreateObject(this, _eShooter);

}
void CMissile::OnCollision(CCollider * _pOther)
{
}
void CMissile::OnCollisionEnter(CCollider * _pOther)
{
	CObject* potherObj = _pOther->GetObj();
	if (L"Monster" == potherObj->GetName())
	{
		DeleteObject(this);
	}
}
void CMissile::OnCollisionExit(CCollider * _pOther)
{
}
