#pragma once
#include "UI.h"
#include "Scene.h"
#include "Object.h"

class CObject;
class CScene;


// 반환타입이 void고		이 두 개의 인자가 들어가는 함수를 BTN_FUNC으로 재정의
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

// 함수포인터로 멤버함수 호출할때 문제가 있음
// 멤버함수 포인터는 선언부터가 전역함수 포인터와는 다름
// void(classname)
// 이렇게 하면 toolscene에 있는 멤버함수를 담는 함수 포인터를 만든것

// 이렇게 해도 되지만 typedef void(CScene_Tool::*TOOL_SCENE_MEMFUNC)(void);
typedef void(CScene::*SCENE_MEMFUNC)(void);
// 이렇게 부모타입으로 만들면 자식들 멤버의 함수까지 받아쓸수있음
// 모든 클래스의 함수를 다 받고 싶으면 우리 프로젝트에서는 모두를 아우르는 최상위 부모를 만들자
// 귀찮아서 안할거
typedef void(CObject::*OBJECT_MEMFUNC)(void);


class CBtnUI :
	public CUI
{
private:
	BTN_FUNC		m_pFunc;
	DWORD_PTR		m_param1;
	DWORD_PTR		m_param2;

	SCENE_MEMFUNC	m_pSceneFunc;

	// 함수를 실행한 인스턴스
	CScene*			m_pSceneInst;



public:
	CBtnUI();
	~CBtnUI();

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();


	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
	{
		m_pFunc = _pFunc;
		m_param1 = _param1;
		m_param2 = _param2;
	}

	void SetClickedCallBack(SCENE_MEMFUNC _pSceneFunc, CScene* _pScene)
	{
		m_pSceneFunc = _pSceneFunc;
		m_pSceneInst = _pScene;
	}

	CLONE(CBtnUI);
};

