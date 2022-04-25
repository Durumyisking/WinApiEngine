#include "pch.h"
#include "Tile.h"

#include "Texture.h"


CTile::CTile()
	: m_pTileTex(nullptr)
	, m_iImgIdx(0)
{
	SetScale(Vec2(ROCK_SIZE, ROCK_SIZE));
}


CTile::~CTile()
{
}


void CTile::update()
{
}

void CTile::render(HDC _dc)
{
	if (nullptr == m_pTileTex || -1 == m_iImgIdx)
		return;

	UINT iWidth = m_pTileTex->GetWidth();
	UINT iHeight = m_pTileTex->GetHeight();

	UINT iMaxCol = iWidth / ROCK_SIZE;
	UINT iMaxRow = iHeight / ROCK_SIZE;

	UINT iCurRow = (UINT)m_iImgIdx / iMaxCol;
	UINT iCurCol = (UINT)m_iImgIdx % iMaxCol;


	if (iMaxRow <= iCurRow)
		assert(nullptr);

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale(); 

	BitBlt(_dc
		, int(vRenderPos.x)
		, int(vRenderPos.y)
		, int(vScale.x)
		, int(vScale.y)
		, m_pTileTex->GetDC()
		, iCurCol * ROCK_SIZE
		, iCurRow * ROCK_SIZE
		, SRCCOPY);
}

void CTile::Save(FILE * _pFile)
{
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE * _pFile)
{
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}
