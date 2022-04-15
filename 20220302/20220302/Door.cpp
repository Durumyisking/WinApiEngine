#include "pch.h"
#include "Door.h"

#include "Texture.h"
#include "Collider.h"

#include "Core.h"

#include "ResMgr.h"




CDoor::CDoor()
	:m_pTex(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"DoorTex", L"texture\\BackGround\\door_01_normaldoor.bmp");


	
	SetScale(Vec2(128.f, 116.f));

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(128.f, 116.f));
}
	

CDoor::~CDoor()
{
}

void CDoor::update()
{

	
}

void CDoor::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width() / 2;
	int iHeight = (int)m_pTex->Height() / 5;


	Vec2 vScale = GetScale();	
	Vec2 vPos = GetPos();
	
	TransparentBlt(_dc
		, (int)(vPos.x - (float)(vScale.x / 2))
		, (int)(vPos.y - (float)(vScale.y / 2))
		, vScale.x, vScale.y
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
	
	component_render(_dc);
}
