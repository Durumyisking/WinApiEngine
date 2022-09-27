#include "pch.h"
#include "EventMgr.h"

#include "Object.h"
#include "SceneMgr.h"
#include "Scene.h"

#include "UIMgr.h"
#include "AI.h"
#include "State.h"

CEventMgr::CEventMgr()
{
}


CEventMgr::~CEventMgr()
{
}

void CEventMgr::init()
{
}

void CEventMgr::update()
{
	// obj �������� vecdead ����
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		// ���� ����������
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	// Event ó��
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Execute(m_vecEvent[i]);
	}

	m_vecEvent.clear(); // ó���� �̺�Ʈ �� ������ ������ �� ����
}

void CEventMgr::Execute(const tEvent & _eve)
{

	switch (_eve.eEvent)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Obj Adr
		// wParam : Group Type
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{	
		/*
		 ���� �̺�Ʈ�� ������ �ٷ� delete���ִ°� �ƴ϶�
		 vecdead�� ���� �־ �����Ұ��̶�� �˷��ְ�
		 ���� ������ update�� �����Ұ��̶�� ���ذŶ� ���� ����
		 �̺�Ʈ ó�� �κп��� �ϰ������� ��������
		*/
		// lParam : Obj Adr
		// Obj�� Dead ���·� ���� => ������ Obj���� ��Ƶд�
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
		// lParam : Next Scene Type
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);

		// focus ui ����
		CUIMgr::GetInst()->SetFocusedUI(nullptr);
		break;

	case EVENT_TYPE::CHANGE_AI:
		// wParam : AI
		// lParam : �ٲ� ai state type
	{
		CAI* pAI = (CAI*)_eve.lParam;
		pAI->SetCurState(static_cast<MON_STATE>(_eve.wParam));
	}
	default:
		break;
	}
}
