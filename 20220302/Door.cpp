#include "pch.h"
#include "Door.h"

#include "Texture.h"
#include "Collider.h"

#include "Core.h"

#include "ResMgr.h"
#include "Room.h"



CDoor::CDoor(CRoom* _pOwner)
	:m_pTex(nullptr)
	,m_pOwner(m_pOwner)
{
	
	m_bOpen = true;
	m_pTex = CResMgr::GetInst()->LoadTexture(L"DoorTex", L"texture\\BackGround\\DoorNS.bmp");
	
	int iWidth = (int)m_pTex->GetWidth() / 2;
	int iHeight = (int)m_pTex->GetHeight() / 2;

	SetScale(Vec2(128.f, 116.f));
	SetName(L"Door");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(90.f, 90.f));

	//m_pTex->GetRotatedBitmap(0, 0, GetScale().x, GetScale().y, 180.);

}


CDoor::~CDoor()
{
}

void CDoor::update()
{


}

void CDoor::render(HDC _dc)
{
	int iWidth = (int)m_pTex->GetWidth() / 2;
	int iHeight = (int)m_pTex->GetHeight() / 2;


	Vec2 vScale = GetScale();
	Vec2 vPos = GetPos();

	TransparentBlt(_dc
		, static_cast<int>(vPos.x - (float)(vScale.x / 2))
		, static_cast<int>(vPos.y - (float)(vScale.y / 2))
		, static_cast<int>(vScale.x), static_cast<int>(vScale.y)
		, m_pTex->GetDC()
		, m_iSliceX, m_iSliceY, iWidth, iHeight
		, RGB(255, 0, 255));

	component_render(_dc);
}

