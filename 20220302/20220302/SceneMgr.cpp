#include "pch.h"
#include "SceneMgr.h"


#include "Scene_Start.h"
#include "Scene_Tool.h"

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
	
	m_pCurScene->Exit();

	m_pCurScene = m_arrScene[(UINT)_eNext];

	m_pCurScene->Enter();
}

void CSceneMgr::init()
{
	// Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");
	//m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Stage01;
	//m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Stage02;

	// 현재 씬 설정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
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
