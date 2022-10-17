#include "pch.h"
#include "SceneMgr.h"


#include "Scene_Start.h"
#include "Scene_Tool.h"
#include "Scene_Menu.h"

#include"EventMgr.h"

CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{
}


CSceneMgr::~CSceneMgr()
{
	// �� ���� ����
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if(nullptr != m_arrScene[i])
			delete m_arrScene[i];
	}
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{

	// ���⼭ Scene�� �ٷ� �ٲٸ� ������ ���� ȣ�⽺�ÿ��� ����Ű��scene�� �޶� ����
	// �׷��� �̺�Ʈ ó��ó�� ��Ƽ� ���� �����ӿ� �ٲ����	
	m_pPrevScene = m_pCurScene;	

	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)_eNext];
	m_pCurScene->Enter();
}

void CSceneMgr::init()
{
	// Scene ����
	m_arrScene[(UINT)SCENE_TYPE::MENU] = new CScene_Menu;
	m_arrScene[(UINT)SCENE_TYPE::MENU]->SetName(L"Menu Scene");
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");

	// ���� �� ����
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
