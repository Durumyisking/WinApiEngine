#include "pch.h"
#include "Scene.h"

#include "Core.h"
#include "Object.h"
#include "Texture.h"
#include "Tile.h"
#include "Door.h"

#include "SceneMgr.h"
#include "ResMgr.h"
#include "TimeMgr.h"
#include "PathMgr.h"
#include "Collider.h"
#include "KeyMgr.h"

#include "SelectGDI.h"

#include "WallCollider.h"
#include "Map.h"
#include "Camera.h"



CScene::CScene()
	: m_fTimeCount(0)
	, m_vResolution(CCore::GetInst()->GetResolution())
	, m_pBgTex(nullptr)
	, m_iTileX(0)
	, m_iTileY(0)
	, m_pMap(nullptr)
	, m_pPlayer(nullptr)
{

	CCamera::GetInst()->SetLookAt(m_vResolution / 2.f);
}


CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		// m_arrObj[i]�� ���� �Ҹ��ڰ� ȣ�� �� �� �ڵ����� vector �Ҹ��ڸ� �θ���
		// ���Ͱ� CScene�� ����ϱ�!
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			delete m_arrObj[i][j];
		}
	}
}

void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	for (size_t i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		if ((UINT)GROUP_TYPE::PLAYER == i || (UINT)GROUP_TYPE::COSTUME == i)
			continue;
			Safe_Delete_Vec<CObject*>(m_arrObj[i]);
	}
	m_pMap->~CMap();
	delete m_pMap;
}

void CScene::DeleteAll_IncludePlayer()
{
	for (size_t i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		Safe_Delete_Vec<CObject*>(m_arrObj[i]);
	}
	m_pMap->~CMap();
	delete m_pMap;
}

void CScene::update()
{
	m_fTimeCount += fDT;

	if (KEY_TAP(KEY::T))
	{
		for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
		{
			for (size_t j = 0; j < m_arrObj[i].size(); ++j)
			{
				if(nullptr != m_arrObj[i][j]->GetCollider())
					m_arrObj[i][j]->GetCollider()->ToggleRenderSwitch();
			}
		}
	}
	
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (!m_arrObj[i][j]->IsDead())
				m_arrObj[i][j]->update(); 
		}
	}

}

void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) 
		{
			m_arrObj[i][j]->finalupdate();
		}
	}

}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		if ((UINT)GROUP_TYPE::TILE == i)
		{
			renderTile(_dc);
			continue;
		}
	
		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->render(_dc);
				++iter;
			}
			else
			{

				iter = m_arrObj[i].erase(iter);				
			}
		}
	}
}

void CScene::renderTile(HDC _dc)
{
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	// ���� ī�޶� �����ִ� ���� �˾ƾ� �� ������ŭ�� ��� ����
	Vec2 vCamLook = CCamera::GetInst()->GetLookAt();
	Vec2 vLeftTop = vCamLook - m_vResolution / 2.f;

	int iTileSize = TILE_SIZE;

	// ����� �Ƴ� �����δ� Ÿ�� idx�� �����ؾ���
	// �ֳ��ϸ� �츮�� 2�������� ���� ���س��ڳ�
	int iLTCol = static_cast<int>(vLeftTop.x) / iTileSize;
	int iLTRow = static_cast<int>(vLeftTop.y) / iTileSize;
	
	// ���� ���ο� �� �� �ִ� �ִ� Ÿ�� ����
	// ������ ���� ©���� +1 
	int iClientWidth = (static_cast<int>(m_vResolution.x) / iTileSize) + 1;
	int iClientHeight = (static_cast<int>(m_vResolution.y) / iTileSize) + 1;

	// 0,0Ÿ�Ϻ��� ���鼭 ������ ����
	for (int iCurRow = iLTRow; iCurRow < (iLTRow + iClientHeight); ++iCurRow)
	{
		for (int iCurCol = iLTCol; iCurCol < (iLTCol + iClientWidth); ++iCurCol)
		{
			// �������� ����(resolution)���� ���������� �ε��� ��� �� ������ ����
			if (iCurCol < 0 || iCurCol >= static_cast<int>(m_iTileX) ||
				iCurRow < 0 || iCurRow >= static_cast<int>(m_iTileY))
			{
				continue;
			}
			// idx = (Ÿ�� ���� * row) + col
			// for�� �� Ÿ���� idx ���Ѱ� 
			int iIdx = (m_iTileX * iCurRow) + iCurCol;
			vecTile[iIdx]->render(_dc);
			
		}
	}

}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	DeleteGroup(GROUP_TYPE::TILE);

	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\BackGround\\rocks_basement.bmp");

	for (UINT i = 0; i < _iYCount; ++i)
	{
		for (UINT j = 0; j < _iXCount; ++j)
		{
			CTile* pTile = new CTile();
			pTile->SetPos(Vec2((float)(j* ROCK_SIZE), (float)(i * ROCK_SIZE)));
			pTile->SetTexture(pTileTex);

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}

void CScene::LoadTile(const wstring & _strRelativePath)
{

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	assert(pFile);

	// Ÿ�� ���� �ҷ�����
	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	// ����Ÿ�� ������ �ҷ����� 
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}


	fclose(pFile);
}




