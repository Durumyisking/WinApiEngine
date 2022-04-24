#pragma once
#include "UI.h"

// 반환타입이 void고		이 두 개의 인자가 들어가는 함수를 BTN_FUNC으로 재정의
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

class CBtnUI :
	public CUI
{
private:
	BTN_FUNC		m_pFunc;
	DWORD_PTR		m_param1;
	DWORD_PTR		m_param2;

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

	CLONE(CBtnUI);
};

