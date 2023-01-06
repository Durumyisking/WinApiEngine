#include "pch.h"
#include "Scene_StageCut.h"

#include "SceneMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Core.h"
#include "Camera.h"
#include "KeyMgr.h"

#include "TimeMgr.h"
#include "Scene_Start.h"

CScene_StageCut::CScene_StageCut()
	: m_pTexBG(nullptr)
	, m_pTexPortrait(nullptr)
	, m_pTexNightmare(nullptr)
	, m_pTexNightmareBubble(nullptr)
	, m_fAnimTimer(0.f)
	, m_fTrumble(5.f)
{
	m_pTexBG = CResMgr::GetInst()->LoadTexture(L"StageCutSceneBG",					L"texture\\CutScene\\nightmares_bg.bmp");
	m_pTexPortrait = CResMgr::GetInst()->LoadTexture(L"StageCutScenePortrait",		L"texture\\CutScene\\playerportraitbig_01_isaac.bmp");
	m_pTexNightmare = CResMgr::GetInst()->LoadTexture(L"StageCutSceneNightmare",	L"texture\\CutScene\\nightmare_1.bmp");
	m_pTexNightmareBubble = CResMgr::GetInst()->LoadTexture(L"StageCutSceneBubble",	L"texture\\CutScene\\nightmare_bubbles.bmp");
}

CScene_StageCut::~CScene_StageCut()
{
}

void CScene_StageCut::Enter()
{

	CSoundMgr::GetInst()->Play(L"stageintro");

	CCore::GetInst()->DivideMenu();
}

void CScene_StageCut::Exit()
{

	CSoundMgr::GetInst()->Stop(L"stageintro", true);
	m_fAnimTimer = 0.f;

}

void CScene_StageCut::update()
{

	if (KEY_TAP(KEY::SPACE))
	{
		// 현재스테이지에서 1더해서 다음스테이지로 ㄱㄱ한다.
		int stage = dynamic_cast<CScene_Start*>(CSceneMgr::GetInst()->GetPrevScene())->GetStage();
		dynamic_cast<CScene_Start*>(CSceneMgr::GetInst()->GetPrevScene())->SetStageIdx(stage + 1);
		dynamic_cast<CScene_Start*>(CSceneMgr::GetInst()->GetPrevScene())->Exit(1);

		CSceneMgr::GetInst()->ChangeScene(SCENE_TYPE::START);
	}

	if (m_fAnimTimer > 4.2f)
		m_fAnimTimer = 2.2f;

	m_fTrumble = -m_fTrumble;

	m_fAnimTimer += fDT;
}

void CScene_StageCut::render(HDC _dc)
{
	// 배경
	int iWidth = static_cast<int>(m_pTexBG->GetWidth());
	int iHeight = static_cast<int>(m_pTexBG->GetHeight());

	StretchBlt(_dc
		, 0, 0
		, static_cast<int>(m_vResolution.x), static_cast<int>(m_vResolution.y)
		, m_pTexBG->GetDC()
		, 0, 0, iWidth, iHeight, SRCCOPY);

	// 초상화
	iWidth = static_cast<int>(m_pTexPortrait->GetWidth());
	iHeight = static_cast<int>(m_pTexPortrait->GetHeight());

	TransparentBlt(_dc
		, static_cast<int>((m_vResolution.x / 2) - (iWidth / 2) - 50.f + m_fTrumble), static_cast<int>((m_vResolution.y / 2) + 100.f)
		, iWidth * 2, iHeight * 2
		, m_pTexPortrait->GetDC()
		, 0, 0, iWidth, iHeight, RGB(255, 0, 255));

	if (m_fAnimTimer > 1.f)
	{
		TransparentBlt(_dc
			, static_cast<int>((m_vResolution.x / 2) - 50.f), static_cast<int>((m_vResolution.y / 2) + 50.f)
			, 32 * 2, 32 * 2
			, m_pTexNightmareBubble->GetDC()
			, 320, 64, 32, 32, RGB(255, 0, 255));
	}

	if (m_fAnimTimer > 1.5f)
	{
		TransparentBlt(_dc
			, static_cast<int>((m_vResolution.x / 2) - 100.f), static_cast<int>((m_vResolution.y / 2) - 30.f)
			, 64 * 2, 64 * 2
			, m_pTexNightmareBubble->GetDC()
			, 320, 0, 64, 64, RGB(255, 0, 255));
	}

	if (m_fAnimTimer > 2.f)
	{
		TransparentBlt(_dc
			, static_cast<int>((m_vResolution.x / 2) - 320.f), static_cast<int>((m_vResolution.y / 2) - 300.f)
			, 320 * 2, 160 * 2
			, m_pTexNightmareBubble->GetDC()
			, 0, 0, 320, 160, RGB(255, 0, 255));
	}

	if (m_fAnimTimer > 2.2f && m_fAnimTimer < 3.2f)
	{
		TransparentBlt(_dc
			, static_cast<int>((m_vResolution.x / 2) - 160.f + m_fTrumble), static_cast<int>((m_vResolution.y / 2) - 280.f)
			, 160 * 2, 128 * 2
			, m_pTexNightmare->GetDC()
			, 0, 128, 160, 128, RGB(255, 0, 255));
	}


	if (m_fAnimTimer > 3.2f)
	{
		TransparentBlt(_dc
			, static_cast<int>((m_vResolution.x / 2) - 160.f + m_fTrumble), static_cast<int>((m_vResolution.y / 2) - 280.f)
			, 160 * 2, 128 * 2
			, m_pTexNightmare->GetDC()
			, 160, 128, 160, 128, RGB(255, 0, 255));
	}

}
