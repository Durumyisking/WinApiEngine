#pragma once
#include "Res.h"
class CTexture :
	public CRes
{

private:
	// 둘 다 4바이트 정수
	HDC			m_dc;
	HBITMAP		m_hBit;
	BITMAP		m_bitInfo;


private: // 우리가 자체적으로 동적할당 불가능하게 private으로 함
		// 일단 safe delete에서 사용 가능하게 public 해둠
	CTexture();
	virtual ~CTexture();

	

public:
	void Load(const wstring& _strFilePath);

	UINT Width() { return m_bitInfo.bmWidth; }
	UINT Height() { return m_bitInfo.bmHeight; }

	HDC GetDC() { return m_dc; }
	HBITMAP GetHBIT() { return m_hBit; }

	// HBITMAP Rotate(HDC _dc, HBITMAP _hBit, float _fRadian);

	void GetRotatedBitmap(float angle);


	friend class CResMgr;
};

