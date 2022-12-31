#include "pch.h"
#include "Scene_Boss.h"

#include "SceneMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Core.h"
#include "Camera.h"
#include "KeyMgr.h"

#include "TimeMgr.h"
#include "Scene_Start.h"

CScene_Boss::CScene_Boss()
	: m_pTexBG(nullptr)
	, m_pTexBoss(nullptr)
	, m_pTexName(nullptr)
	, m_pTexPlayer(nullptr)
	, m_vPlayerSlice(Vec2(0.f, 0.f))
	, m_vBossSlice(Vec2(4.f, 0.f))
	, m_vVSSlice(Vec2(100.f, 100.f))
	, m_vSliceValue(Vec2(224.f, 64.f))
	, m_fAnimValue(0.f)
	, m_bAnimReverse(false)
	, m_fAnimTimer(0.f)
	, m_bIsAnimTimerOn(false)
	, m_fAnimMoveQuan(1500.f)
	, m_pTexPlayerfloor(nullptr)
	, m_pTexBossfloor(nullptr) 
{

	m_pTexBG = CResMgr::GetInst()->LoadTexture(L"BossSceneBG", L"texture\\CutScene\\bgblack.bmp");
	m_pTexBoss = CResMgr::GetInst()->LoadTexture(L"BossSceneBoss", L"texture\\CutScene\\portrait_dangle.bmp");
	m_pTexName = CResMgr::GetInst()->LoadTexture(L"BossSceneName", L"texture\\CutScene\\vsnames.bmp");
	m_pTexPlayer = CResMgr::GetInst()->LoadTexture(L"BossScenePlayer", L"texture\\CutScene\\playerportrait_01_isaac.bmp");
	m_pTexBossfloor = CResMgr::GetInst()->LoadTexture(L"BossSceneBossFloor", L"texture\\CutScene\\bossspot.bmp");
	m_pTexPlayerfloor = CResMgr::GetInst()->LoadTexture(L"BossScenePlayerFloor", L"texture\\CutScene\\playerspot.bmp");

}

CScene_Boss::~CScene_Boss()
{
}

void CScene_Boss::Enter()
{
	CCore::GetInst()->DivideMenu();
}

void CScene_Boss::Exit()
{

}

void CScene_Boss::update()
{
	int stage = dynamic_cast<CScene_Start*>(CSceneMgr::GetInst()->GetPrevScene())->GetStage();
	if (1 == stage)
	{
		SetBoss(MON_TYPE::Dangle);
	}
	else if (2 == stage)
	{
		SetBoss(MON_TYPE::Monstro);
	}

	if (m_bIsAnimTimerOn)
	{
		m_fAnimTimer += fDT;
		if (m_fAnimTimer > 0.25f)
			m_bIsAnimTimerOn = false;

	}
	
	if(!m_bIsAnimTimerOn)
	{
		// 애님타이머가 켜져있지 않으면 화면 중앙으로 이동
		if (m_bAnimReverse)
			m_fAnimValue -= m_fAnimMoveQuan * fDT;
		else
			m_fAnimValue += m_fAnimMoveQuan * fDT;
	}

	// 슬로우모션으로
	if (m_fAnimValue > 400.f && m_fAnimMoveQuan > 150.f && m_bAnimReverse == false)
	{
		m_fAnimMoveQuan -= 200.f;
	}

	if (m_fAnimValue > 550.f)
	{
		m_fAnimMoveQuan = 1500.f;
		m_bIsAnimTimerOn = true;
		m_bAnimReverse = true;
	}

	// 다시 스타트씬으로 전환
	if (m_bAnimReverse && m_fAnimValue < 0.f || KEY_TAP(KEY::SPACE))
	{
		m_bIsAnimTimerOn = false;
		m_fAnimMoveQuan= 1500.f;
		m_fAnimTimer = 0.f;
		m_fAnimValue = 0.f;
		m_bAnimReverse = false;

		CCamera::GetInst()->FadeIn(1.f);
		CSceneMgr::GetInst()->SetCurScene(SCENE_TYPE::START);
	}
	
}

void CScene_Boss::render(HDC _dc)
{
		// 배경
		int iWidth = static_cast<int>(m_pTexBG->GetWidth());
		int iHeight = static_cast<int>(m_pTexBG->GetHeight());

		StretchBlt(_dc
			, 0, 0
			, static_cast<int>(m_vResolution.x), static_cast<int>(m_vResolution.y)
			, m_pTexBG->GetDC()
			, 0, 0, iWidth, iHeight, SRCCOPY);

		// 보스 바닥
		iWidth = static_cast<int>(m_pTexBossfloor->GetWidth());
		iHeight = static_cast<int>(m_pTexBossfloor->GetHeight());

		TransparentBlt(_dc
			, 1250 - static_cast<int>(m_fAnimValue), 500 
			, 260 * 2, 70 * 2
			, m_pTexBossfloor->GetDC()
			, 0, 0, iWidth, iHeight, RGB(255, 0, 255));
	
		// 플레이어 바닥
		iWidth = static_cast<int>(m_pTexPlayerfloor->GetWidth());
		iHeight = static_cast<int>(m_pTexPlayerfloor->GetHeight());

		TransparentBlt(_dc
			, -356 + static_cast<int>(m_fAnimValue), 580 // , 150, 400
			, 172 * 2, 46 * 2
			, m_pTexPlayerfloor->GetDC()
			, 0, 0, iWidth, iHeight, RGB(255, 0, 255));

		// 보스 초상화
		iWidth = static_cast<int>(m_pTexBoss->GetWidth());
		iHeight = static_cast<int>(m_pTexBoss->GetHeight());

		TransparentBlt(_dc
			, 1330 - static_cast<int>(m_fAnimValue) , 300 // , 800, 300
			, 192 * 2, 192 * 2
			, m_pTexBoss->GetDC()
			, 0, 0, iWidth, iHeight, RGB(255, 0, 255));

		// 보스 이름
		iWidth = static_cast<int>(m_vSliceValue.x);
		iHeight = static_cast<int>(m_vSliceValue.y);
		Vec2 vResult = m_vBossSlice * m_vSliceValue;
		TransparentBlt(_dc
			, 1280 - static_cast<int>(m_fAnimValue), 150 // , 750, 150
			, 224 * 2, 64 * 2
			, m_pTexName->GetDC()
			, static_cast<int>(vResult.x), static_cast<int>(vResult.y), iWidth, iHeight, RGB(255, 0, 255));


		// 플레이어 초상화
		iWidth = static_cast<int>(m_pTexPlayer->GetWidth());
		iHeight = static_cast<int>(m_pTexPlayer->GetHeight());

		TransparentBlt(_dc
			, -366 + static_cast<int>(m_fAnimValue), 400 // , 150, 400
			, 112 * 3, 78 * 3
			, m_pTexPlayer->GetDC()
			, 0, 0, iWidth, iHeight, RGB(255, 0, 255));
				
		// 플레이어 이름
		iWidth = static_cast<int>(m_vSliceValue.x);
		iHeight = static_cast<int>(m_vSliceValue.y);
		vResult = m_vPlayerSlice * m_vSliceValue;
		TransparentBlt(_dc
			, -448 + static_cast<int>(m_fAnimValue), 150 // , 120, 150
			, 224 * 2, 64 * 2
			, m_pTexName->GetDC()
			, static_cast<int>(vResult.x), static_cast<int>(vResult.y), iWidth, iHeight, RGB(255, 0, 255));

		// VS
		vResult = m_vPlayerSlice * m_vSliceValue;
		TransparentBlt(_dc
			, 550, 150 // , 550, 150
			, 100 * 2, 100 * 2
			, m_pTexName->GetDC()
			, 0, 80, 100, 100, RGB(255, 0, 255));




	CScene::render(_dc);
}


