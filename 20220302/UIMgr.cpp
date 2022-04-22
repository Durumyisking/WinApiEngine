#include "pch.h"
#include "UIMgr.h"

#include "UI.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Camera.h"
#include "KeyMgr.h"

#include "Object.h"



CUIMgr::CUIMgr()
{


	
}

CUIMgr::~CUIMgr()
{



}

void CUIMgr::update()
{
	CScene* pcurScene = CSceneMgr::GetInst()->GetCurScene();

	Vec2 vMousePos = MOUSE_POS;
	const vector<CObject*>& vecUI = pcurScene->GetGroupObject(GROUP_TYPE::UI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{		
		CUI* pUI = (CUI*)vecUI[i];

		pUI = GetTargetedUI(pUI);

		if (nullptr != pUI)
		{
			pUI->MouseOn();

			if (bLbtnTap)
			{
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true;
			}
			// 타겟 UI만 체크
			else if (bLbtnAway)
			{
				pUI->MouseLbtnUp();

				if (pUI->m_bLbtnDown)
				{
					pUI->MouseLbtnClicked();
				}

				pUI->m_bLbtnDown = false;
			}
		}
	}
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
