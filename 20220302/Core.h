#pragma once

class CTexture;

class CCore
{
	SINGLE(CCore);

private:
	HWND	m_hWnd;
	Vec2	m_vResolution;
	HDC		m_hDC;

	CTexture* m_pMemTex; // 백버퍼 텍스처

	// 자주 사용하는 GDI OBJ
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];;

	// 메뉴
	HMENU	m_hMenu; // Tool Scene에서만 사용하고싶은 menu



public:
	int init(HWND _hWnd, Vec2 _vResolution);
	void progress();

private:
	void Clear();
	void CreateBrushPen();

public:
	void DockingMenu();
	void DivideMenu();
	void ChangeWindowSize(bool _bMenu);

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	Vec2 GetResolution() { return m_vResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
	HMENU GetMenu() { return m_hMenu; };
};