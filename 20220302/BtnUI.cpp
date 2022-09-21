#include "pch.h"
#include "BtnUI.h"



CBtnUI::CBtnUI()
	:CUI(false)
	, m_pFunc(nullptr)
	, m_param1(0)
	, m_param2(0)
	, m_pSceneInst(nullptr)
	, m_pSceneFunc(nullptr)
{
}

CBtnUI::~CBtnUI()
{
}

void CBtnUI::MouseOn()
{
}

void CBtnUI::MouseLbtnDown()
{
}

void CBtnUI::MouseLbtnUp()
{
}

void CBtnUI::MouseLbtnClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_param1, m_param2);
	}


	if (m_pSceneInst && m_pSceneFunc)
	{
		// 객체로 멤버함수 포인터 호출할때
				
		// * 기호로 원본으로 접근후   함수도 포인터로 받아왔으니까*로 접근
		((*m_pSceneInst).*m_pSceneFunc)();
	}
}
