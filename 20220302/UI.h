#pragma once
#include "Object.h"

class CTexture;

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
	float				m_fMagnify;

protected:
	CTexture*			m_pTex;
	Vec2				m_vSlice;



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
	CUI* GetParent() const { return m_pParentUI; }
	void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }

	const vector<CUI*>& GetChildUI() const { return m_vecChildUI; }

	Vec2 GetFinalPos() const { return m_vFinalPos; }

	Vec2 GetSlice() { return m_vSlice; }
	void SetSlice(Vec2 _vSlice) { m_vSlice = _vSlice; }

	bool IsMouseOn() { return m_bMouseOn; }

	bool IsLbtnDown() { return m_bLbtnDown; }

	void SetMagnify(float _fValue) { m_fMagnify = _fValue; }
	float GetMagnify() const { return m_fMagnify; }

	void SetTexture(CTexture* _pTex)
	{
		m_pTex = _pTex;
	}

};

