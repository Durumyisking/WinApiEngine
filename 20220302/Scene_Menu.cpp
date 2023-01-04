#include "pch.h"
#include "Scene_Menu.h"

#include "SceneMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Core.h"

#include "MenuObj.h"
#include "Camera.h"

#include "KeyMgr.h"

CScene_Menu::CScene_Menu()
	: m_bOnNewGame(false)
	, m_pTexStart(nullptr)
	, m_pTexNewRun(nullptr)

{
	m_pTexStart = CResMgr::GetInst()->LoadTexture(L"titlemenuTex", L"texture\\UI\\titlemenu.bmp");
	m_pTexNewRun = CResMgr::GetInst()->LoadTexture(L"gamemenuTex", L"texture\\UI\\gamemenudemo.bmp");
}

CScene_Menu::~CScene_Menu()
{
}

void CScene_Menu::Enter()
{
	CSoundMgr::GetInst()->Play(L"intro");

	CCamera::GetInst()->FadeIn(0.5f);

	CCore::GetInst()->DivideMenu();

	CObject* pTitle = new CMenuObj(L"titlemenu");
	CObject* pTitleMenu = new CMenuObj(L"title");
	CObject* pGameMenu = new CMenuObj(L"gamemenu");


	CreateObject(pTitle, GROUP_TYPE::UI);
	CreateObject(pTitleMenu, GROUP_TYPE::UI);
	CreateObject(pGameMenu, GROUP_TYPE::UI);

}

void CScene_Menu::Exit()
{
//	m_pMap
	CCamera::GetInst()->SetLookAt(m_vResolution / 2.f);
	
	DeleteAll();
}

void CScene_Menu::update()
{

	if (KEY_TAP(KEY::SPACE))
	{
		if (m_bOnNewGame)
		{
			CSoundMgr::GetInst()->Stop(L"intro", true);
			CSoundMgr::GetInst()->Play(L"introtostart");
			ChangeScene(SCENE_TYPE::START);
		}
		else
		{ 
			CCamera::GetInst()->SetLookAt(Vec2(m_vResolution.x/2, m_vResolution.y + m_vResolution.y/2));
			m_bOnNewGame = true;
		}
	}
	else if (KEY_TAP(KEY::ESC))
	{
		if (!m_bOnNewGame)
			ChangeScene(SCENE_TYPE::TOOL);
		else
		{
			CCamera::GetInst()->SetLookAt(m_vResolution / 2.f);
			m_bOnNewGame = false;
		}
	}

}

void CScene_Menu::render(HDC _dc)
{

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vResolution);;

	int iWidth = (int)m_pTexStart->GetWidth();
	int iHeight = (int)m_pTexStart->GetHeight();


	StretchBlt(_dc, static_cast<int>(vRenderPos.x - m_vResolution.x), static_cast<int>(vRenderPos.y - m_vResolution.y)
		, static_cast<int>(m_vResolution.x), static_cast<int>(m_vResolution.y), m_pTexStart->GetDC(), 0, 0, iWidth, iHeight, SRCCOPY);

	StretchBlt(_dc, static_cast<int>(vRenderPos.x - m_vResolution.x), static_cast<int>(vRenderPos.y)
		, static_cast<int>(m_vResolution.x), static_cast<int>(m_vResolution.y), m_pTexNewRun->GetDC(), 0, 0, iWidth, iHeight, SRCCOPY);


	CScene::render(_dc);
}
