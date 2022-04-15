#include "pch.h"
#include "UI.h"


// 모든 UI의 부모로써 추상 클래스로 객체 생성 못하게 할거임
// UI들은 부모 자식관계를 가짐
// Scene에는 가장 최상위 부모 단 하나만 넣어줄 것임



CUI::CUI()
{
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}

void CUI::update()
{
	update_child();
}

// 최종 위치를 설정해줌
void CUI::finalupdate()
{
	CObject::finalupdate();

	m_vFinalPos = GetPos();

	// UI의 최종 좌표를 구한다.
	if (GetParent())
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}

	finalupdate_child();

}

void CUI::render(HDC _dc)
{
	// 그냥 getpos라고 하면 vParnetpos가 더해지지 않은 초기화 위치로 설정됨
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();


	Rectangle(_dc
		, int(vPos.x)
		, int(vPos.y)
		, int(vPos.x + vScale.x)
		, int(vPos.y + vScale.y));

	render_child(_dc);
}

void CUI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finalupdate();
	}

}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

