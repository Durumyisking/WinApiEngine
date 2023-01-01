#include "pch.h"
#include "Scene_Ending.h"
#include "ResMgr.h"
#include "Camera.h"
#include "Texture.h"
#include "Core.h"
#include "KeyMgr.h"

CScene_Ending::CScene_Ending()
	:m_pTexBG(nullptr)
{
	m_pTexBG = CResMgr::GetInst()->LoadTexture(L"EndTex", L"texture\\UI\\ending.bmp");

}

CScene_Ending::~CScene_Ending()
{
}

void CScene_Ending::Enter()
{
	CCore::GetInst()->DivideMenu();

}

void CScene_Ending::Exit()
{
}

void CScene_Ending::update()
{

	if (KEY_TAP(KEY::SPACE))
	{
		DestroyWindow(CCore::GetInst()->GetMainHwnd());
	}
}

void CScene_Ending::render(HDC _dc)
{
//	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vResolution);;

	int iWidth = (int)m_pTexBG->GetWidth();
	int iHeight = (int)m_pTexBG->GetHeight();


	StretchBlt(_dc
		, 0, 0
		, static_cast<int>(m_vResolution.x), static_cast<int>(m_vResolution.y)
		, m_pTexBG->GetDC()
		, 0, 0, iWidth, iHeight, SRCCOPY);


	CScene::render(_dc);
}
