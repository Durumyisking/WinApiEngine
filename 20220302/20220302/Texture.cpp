#include "pch.h"
#include "Texture.h"

#include "Core.h"

CTexture::CTexture()
	: m_dc(nullptr)
	, m_hBit(nullptr)
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
	// 가능하면 C 스타일 캐스트가 아닌 형변환 연산자를 사용하는 것을 추천함
	m_hBit = static_cast<HBITMAP>(LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE));
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);

	if (nullptr == m_hBit)
	{
		// 이미지 로딩 실패 시
		assert(false);
	}

	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());
	HBITMAP hPrevBit = static_cast<HBITMAP>(SelectObject(m_dc, m_hBit));
	DeleteObject(hPrevBit); // 남아있던 이전의 bitmap 제거

	GetRotatedBitmap(0, 0, static_cast<int>(m_bitInfo.bmWidth), static_cast<int>(m_bitInfo.bmHeight), 180.);
}
void CTexture::GetRotatedBitmap(int source_x, int source_y, int dest_width, int dest_height, double degree)
{
	// 지역 변수들은 선언과 동시에 초기화 해주는 걸 추천함
	// 가끔씩 초기화되지 않은 쓰레기 값이 들어있는 변수가 결과값에 영향을 미치는 경우가 있음

	HDC source_dc = CreateCompatibleDC(m_dc);
	HDC dest_dc = CreateCompatibleDC(m_dc);
	HBITMAP bm_result = CreateCompatibleBitmap(m_dc, dest_width, dest_height);

	HBITMAP hbm_old_source = static_cast<HBITMAP>(SelectObject(source_dc, m_hBit));
	HBITMAP hbm_old_dest = static_cast<HBITMAP>(SelectObject(dest_dc, bm_result));

	HBRUSH brush_back = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH brush_old = static_cast<HBRUSH>(SelectObject(dest_dc, brush_back));

	PatBlt(dest_dc, 0, 0, dest_width, dest_height, PATCOPY);
	DeleteObject(SelectObject(dest_dc, brush_old));

	// degree 값 radian으로 변경
	float cos_theta = static_cast<float>(cos(DegreeToRadian(degree)));
	float sin_theta = static_cast<float>(sin(DegreeToRadian(degree)));

	// 윈도우 좌표계 회전을 위해 그래픽 확장모드 전환
	SetGraphicsMode(dest_dc, GM_ADVANCED);

	XFORM xform = {};
	xform.eM11 = cos_theta;
	xform.eM12 = sin_theta;
	xform.eM21 = -sin_theta;
	xform.eM22 = cos_theta;
	xform.eDx = static_cast<float>(dest_width) / 2.f;
	xform.eDy = static_cast<float>(dest_height) / 2.f;

	SetWorldTransform(dest_dc, &xform);

	// 회전 이미지 출력
	BitBlt(dest_dc, -(dest_width / 2), -(dest_height / 2), dest_width, dest_height, source_dc, source_x, source_y, SRCCOPY);

	// 자원 해제
	SelectObject(source_dc, hbm_old_source);
	SelectObject(dest_dc, hbm_old_dest);
	DeleteObject(source_dc);
	DeleteObject(dest_dc);

	m_hBit = bm_result;
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);

	HBITMAP hPrevBit = static_cast<HBITMAP>(SelectObject(m_dc, m_hBit));
	DeleteObject(hPrevBit); // 남아있던 이전의 bitmap 제거
}



