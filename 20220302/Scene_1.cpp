#include "pch.h"
#include "Scene_1.h"

#include "ResMgr.h"
#include "KeyMgr.h"


CScene_1::CScene_1()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"Scene1", L"texture\\BackGround\\BG_Tool.bmp");
}


CScene_1::~CScene_1()
{
}

void CScene_1::update()
{
	CScene::update();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}
}

void CScene_1::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();


	TransparentBlt(_dc
		, (int)(0.f)
		, (int)(0.f)
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	CScene::render(_dc);
}

void CScene_1::Enter()
{
}

void CScene_1::Exit()
{
}
