#include "pch.h"
#include "EventMgr.h"

#include "Object.h"
#include "SceneMgr.h"
#include "Scene.h"


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
	// obj 쓰레기통 vecdead 비우기
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		// 가장 마지막순서
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	// Event 처리
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Execute(m_vecEvent[i]);
	}

	m_vecEvent.clear(); // 처리된 이벤트 한 프레임 지나면 다 삭제
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
		 삭제 이벤트가 들어오면 바로 delete해주는게 아니라
		 vecdead에 먼저 넣어서 삭제할것이라고 알려주고
		 다음 프레임 update때 삭제할것이라고 해준거랑 연결 끊고
		 이벤트 처리 부분에서 일괄적으로 삭제해줌
		*/
		// lParam : Obj Adr
		// Obj를 Dead 상태로 변경 => 변경한 Obj들을 모아둔다
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);


	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
		// lParam : Next Scene Type
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);


		break;

	default:
		break;
	}
}
