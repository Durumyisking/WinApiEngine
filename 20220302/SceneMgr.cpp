#include "pch.h"
#include "SceneMgr.h"


#include "Scene_Start.h"
#include "Scene_Tool.h"
#include "Scene_Menu.h"
#include "Scene_Intro.h"
#include "Scene_Boss.h"
#include "Scene_StageCut.h"
#include "Scene_Ending.h"

#include"EventMgr.h"

CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{
}


CSceneMgr::~CSceneMgr()
{
	// 씬 전부 삭제
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if(nullptr != m_arrScene[i])
			delete m_arrScene[i];
	}
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{

	// 여기서 Scene을 바로 바꾸면 문제가 이전 호출스택에서 가리키는scene이 달라 문제
	// 그래서 이벤트 처리처럼 모아서 다음 프레임에 바꿔버림	
	m_pPrevScene = m_pCurScene;	

	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)_eNext];
	m_pCurScene->Enter();
}

void CSceneMgr::SetCurScene(SCENE_TYPE _eNext)
{

	m_pPrevScene = m_pCurScene;

   	m_pCurScene = m_arrScene[(UINT)_eNext];
}

void CSceneMgr::init()
{
	// Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::INTRO] = new CScene_Intro;
	m_arrScene[(UINT)SCENE_TYPE::INTRO]->SetName(L"Intro Scene");
	m_arrScene[(UINT)SCENE_TYPE::MENU] = new CScene_Menu;
	m_arrScene[(UINT)SCENE_TYPE::MENU]->SetName(L"Menu Scene");
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");
	m_arrScene[(UINT)SCENE_TYPE::BOSS] = new CScene_Boss;
	m_arrScene[(UINT)SCENE_TYPE::BOSS]->SetName(L"Boss Scene");
	m_arrScene[(UINT)SCENE_TYPE::STAGECUT] = new CScene_StageCut;
	m_arrScene[(UINT)SCENE_TYPE::STAGECUT]->SetName(L"StageCut Scene");
	m_arrScene[(UINT)SCENE_TYPE::ENDING] = new CScene_Ending;
	m_arrScene[(UINT)SCENE_TYPE::ENDING]->SetName(L"Ending Scene");


	// 현재 씬 설정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pPrevScene = m_pCurScene;

	m_pCurScene->Enter();

}

void CSceneMgr::update()
{
	m_pCurScene->update();

	m_pCurScene->finalupdate();
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);

}
