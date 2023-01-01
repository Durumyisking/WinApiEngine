#include "pch.h"
#include "Scene_Intro.h"

#include "SceneMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Core.h"
#include "Camera.h"
#include "KeyMgr.h"


CScene_Intro::CScene_Intro()
	: m_pTexStart(nullptr)
{
	m_pTexStart = CResMgr::GetInst()->LoadTexture(L"IntroTex", L"texture\\UI\\titlemenu.bmp");

}

CScene_Intro::~CScene_Intro()
{
}

void CScene_Intro::Enter()
{
	CCore::GetInst()->DivideMenu();

}

void CScene_Intro::Exit()
{
//	CCamera::GetInst()->FadeOut(0.5f);

}

void CScene_Intro::update()
{


	if (KEY_TAP(KEY::SPACE))
	{
		ChangeScene(SCENE_TYPE::MENU);

	}

}

void CScene_Intro::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vResolution);;

	int iWidth = (int)m_pTexStart->GetWidth();
	int iHeight = (int)m_pTexStart->GetHeight();


	StretchBlt(_dc
		, static_cast<int>(vRenderPos.x - m_vResolution.x), static_cast<int>(vRenderPos.y - m_vResolution.y)
		, static_cast<int>(m_vResolution.x), static_cast<int>(m_vResolution.y)
		, m_pTexStart->GetDC()
		, 0, 0, iWidth, iHeight, SRCCOPY);


	CScene::render(_dc);

}
