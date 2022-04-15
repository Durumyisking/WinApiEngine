#include "pch.h"
#include "Texture.h"

#include "Core.h"

CTexture::CTexture()
	: m_dc(0)
	, m_hBit(0)
	, m_bitInfo{}
{
}


CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}


void CTexture::Load(const wstring & _strFilePath) // 인자의 경로에는 최종적인 경로값이 들어감
{
	/*
		LoadImage(Hinstance, 이미지 경로, 이미지 타입
			, 가로길이, 세로길이, 이미지 로딩 옵션
	*/

	// 마지막 두 인자 에 이미지의 가로 세로를 넣어야 하는데 
	// 이미지는 이미지마다 다 다른 크기를 가지기 때문에 여기서 지정안함
	// 따라서 default인 0을 넣는다

	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP ,0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	assert(m_hBit); // 이미지 로딩 실패시

	// 비트맵을 띄워줄 작은 DC 생성
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	// 비트맵과 DC 연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit); // 남아있던 이전의 bitmap 제거

	//GetRotatedBitmap(0.f);

	// w 468 h 312
	// 가로 세로 길이
	// BITMAP : 비트맵의 각종 정보드를 저장하는 구조체
	// GetObject() : 특정 OBJ들의 정보를 알려주는 함수, 이때 핸들로 넣어주는게 우리의 비트맵
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);

}
void CTexture::GetRotatedBitmap(float radians)
{
	HDC sourceDC, destDC;
	BITMAP bm;

	HBITMAP hbmResult;
	HBITMAP hbmOldSource;
	HBITMAP hbmOldDest;
	HBRUSH hbrBack;
	HBRUSH hbrOld;

	XFORM xform;

	float cosine, sine;
	int x1, y1, x2, y2, x3, y3, minx, miny, maxx, maxy, w, h;

	// 
	sourceDC = CreateCompatibleDC(CCore::GetInst()->GetMainDC());


	destDC = CreateCompatibleDC(CCore::GetInst()->GetMainDC());



	GetObject(m_hBit, sizeof(bm), &bm);

	cosine = cos(radians * 3.14 / 180.f);
	sine = sin(radians * 3.14 / 180.f);


	// 회전된 이미지의 영역을 구한다.
	// 점 3개잡고 설정해준 각도로 돌림
	x1 = (int)(bm.bmHeight * sine);
	y1 = (int)(bm.bmHeight * cosine);

	x2 = (int)(bm.bmWidth * cosine + bm.bmHeight * sine);
	y2 = (int)(bm.bmHeight * cosine - bm.bmWidth * sine);

	x3 = (int)(bm.bmWidth * cosine);
	y3 = (int)(-bm.bmWidth * sine);

	minx = min(0, min(x1, min(x2, x3)));
	miny = min(0, min(y1, min(y2, y3)));
	maxx = max(0, max(x1, max(x2, x3)));
	maxy = max(0, max(y1, max(y2, y3)));


	// 회전된 이미지의 영역
	w = maxx - minx;
	h = maxy - miny;



	// 회전된 이미지 영역 크기의 btimap 생성
	hbmResult = CreateCompatibleBitmap(m_dc, w, h);

	
	hbmOldSource = (HBITMAP)SelectObject(sourceDC, m_hBit);
	hbmOldDest = (HBITMAP)SelectObject(destDC, hbmResult);


	// dc 바꾸기전에 배경그림 이미지 회전시키면 빈공간 생기니까
	hbrBack = CreateSolidBrush(RGB(255,0,255));
	hbrOld = (HBRUSH)SelectObject(destDC, hbrBack);

	// 우리 bitmap 만큼만 다시 그려줌
	PatBlt(destDC, 0, 0, w, h, PATCOPY);

	// 늙은이 지움
	DeleteObject(SelectObject(destDC, hbrOld));

	SetGraphicsMode(destDC, GM_ADVANCED);
	xform.eM11 = cosine;
	xform.eM12 = -sine;

	xform.eM21 = sine;
	xform.eM22 = cosine;

	xform.eDx = (float)-minx;
	xform.eDy = (float)-miny;

	SetWorldTransform(destDC, &xform);


	// 좌표계 바꾼 dc에 비트맵 넣음
	BitBlt(destDC, 0, 0, bm.bmWidth, bm.bmHeight, sourceDC, 0, 0, SRCCOPY);


	// dc 가져옴
	SelectObject(sourceDC, hbmOldSource);
	SelectObject(destDC, hbmOldDest);

	DeleteDC(sourceDC);
	DeleteDC(destDC);



	m_hBit =  hbmResult;
}



