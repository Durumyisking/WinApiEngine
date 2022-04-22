#include "pch.h"
#include "SelectGDI.h"

#include "Core.h"



CSelectGDI::CSelectGDI(HDC _dc, PEN_TYPE _ePenType)
	: m_hDC(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
{
	HPEN hPen = CCore::GetInst()->GetPen(_ePenType);
	m_hDefaultPen = (HPEN)SelectObject(_dc, hPen);

}

CSelectGDI::CSelectGDI(HDC _dc, BRUSH_TYPE _eBrushType)
	: m_hDC(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
{
	HBRUSH hBrush = CCore::GetInst()->GetBrush(_eBrushType);
	m_hDefaultBrush = (HBRUSH)SelectObject(_dc, hBrush);

}

CSelectGDI::~CSelectGDI()
{
	if (nullptr != m_hDefaultPen || nullptr != m_hDefaultBrush)
	{
		SelectObject(m_hDC, m_hDefaultPen);
		SelectObject(m_hDC, m_hDefaultBrush);
	}
	
}
