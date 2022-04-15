#pragma once
class CSelectGDI
{
private:
	HDC		m_hDC;
	HPEN	m_hDefaultPen;
	HBRUSH	m_hDefaultBrush;

public:
	CSelectGDI(HDC _dc, PEN_TYPE _ePenType);
	CSelectGDI(HDC _dc, BRUSH_TYPE _eBrushType);
	~CSelectGDI();
};

