#include "pch.h"
#include "SelectGDI.h"

#include "Core.h"



CSelectGDI::CSelectGDI(HDC _dc, PEN_TYPE _ePenType)
	: m_hDC(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
{
	HPEN hGreenPen = CCore::GetInst()->GetPen(_ePenType);
	HPEN hDefaultPen = (HPEN)SelectObject(_dc, hGreenPen);
}

CSelectGDI::CSelectGDI(HDC _dc, BRUSH_TYPE _eBrushType)
	: m_hDC(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
{
	HBRUSH hHollowBrush = CCore::GetInst()->GetBrush(_eBrushType);
	HBRUSH hDefaultBrush = (HBRUSH)SelectObject(_dc, hHollowBrush);
}

CSelectGDI::~CSelectGDI()
{
	if (nullptr != m_hDefaultBrush || nullptr != m_hDefaultPen)
	{
		SelectObject(m_hDC, m_hDefaultPen);
		SelectObject(m_hDC, m_hDefaultBrush);
	}
}
