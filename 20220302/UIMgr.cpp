#include "pch.h"
#include "UIMgr.h"

#include "UI.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Camera.h"
#include "KeyMgr.h"

#include "Object.h"



CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{}

CUIMgr::~CUIMgr()
{}

void CUIMgr::update()
{

	// FocusedUI 확인 (부모 UI가 들어감)
	m_pFocusedUI = GetFocusedUI();
	if (!m_pFocusedUI)
		return;


	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// FocusedUI 에서 부모 자식 UI들중 실제 타겟팅 된 UI 받아옴
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		if (bLbtnTap)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		// 타겟 UI만 체크
		else if (bLbtnAway)
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->MouseLbtnClicked();
			}

			pTargetUI->m_bLbtnDown = false;
		}
		
	}
}

void CUIMgr::SetFocusedUI(CUI * _pUI)
{
	if (m_pFocusedUI == _pUI || nullptr == m_pFocusedUI || nullptr == _pUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}
	m_pFocusedUI = _pUI;


	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
			break;				
	}

	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}


CUI * CUIMgr::GetFocusedUI()
{
	// 부모 UI들중 현재 포커싱된 UI, 변경이 감지된 UI 가져옴

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// 포커싱 될 때마다 포커싱 되는 UI를 벡터의 맨 뒤로 보내줄것임
	// 기존 포커싱 UI를 받아두고 변경되었는지 확인
	CUI* pFocusedUI = m_pFocusedUI;

	if (!bLbtnTap)
	{
		// 왼쪽 클릭이 없으니 기존의 focusedui 반환
		return pFocusedUI;
	}
	
	// 왼쪽클릭이 발생
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	// focus 된 ui가 없다
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	// 벡터 내에서 맨 뒤로 순번 교체

	// 기존 자리 지우고
	vecUI.erase(targetiter);

	// 저장해두었던 focusedui pushback
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI * CUIMgr::GetTargetedUI(CUI * _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// 1. 부모 포함 모든 자식 UI를 검사
	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;
	static vector<CUI*>  vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// 큐에서 데이터 하나 꺼내기
		CUI* pUI = queue.front();
		queue.pop_front();

		// 큐에서 꺼낸 UI가 TargetUI인지 확인

		// 타겟 UI 들 중, 더 우선순위가 높은 기준은 더 낮은 레벨의 자식

		if (pUI->IsMouseOn())
		{
			// 새로운 UI가 타겟으로 지정되기 전에
			// 기존 타겟 UI도 nonetarget
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}

		// 그 UI의 자식들을 가져옴
		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			// 받아온 자식들을 inqueue
			queue.push_back(vecChild[i]);
		}

		// 논타겟 벡터들만 마우스 버튼 떼져있는거 확인
		if (bLbtnAway)
		{
			for (size_t i = 0; i < vecNoneTarget.size(); ++i)
			{
				vecNoneTarget[i]->m_bLbtnDown = false;
			}
		}
	}

	return pTargetUI;;
}
