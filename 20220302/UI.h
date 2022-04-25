#pragma once
#include "Object.h"



class CUI :
	public CObject
{
private:
	vector<CUI*>		m_vecChildUI;
	CUI*				m_pParentUI;
	Vec2				m_vFinalPos;

	bool				m_bCameAffected; // UI가 카메라 영향을 받는지
	bool				m_bMouseOn;
	bool				m_bLbtnDown;



public:
	CUI(bool _bCameAff);
	CUI(const CUI& _origin);
	~CUI();

	friend class CUIMgr;

	CLONE(CUI);
public:
	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

public:
	void update_child();
	void finalupdate_child();
	void render_child(HDC _dc);

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	
	void MouseOnCheck();

public:
	CUI* GetParent() { return m_pParentUI; }
	void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }

	const vector<CUI*>& GetChildUI() { return m_vecChildUI; }

	Vec2 GetFinalPos() { return m_vFinalPos; }

	bool IsMouseOn() { return m_bMouseOn; }

	bool IsLbtnDown() { return m_bLbtnDown; }

};

