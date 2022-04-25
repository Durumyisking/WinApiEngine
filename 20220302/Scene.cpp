#include "pch.h"
#include "Scene.h"

#include "Core.h"
#include "Object.h"
#include "Texture.h"
#include "Tile.h"

#include "SceneMgr.h"
#include "ResMgr.h"
#include "TimeMgr.h"
#include "PathMgr.h"

#include "Body.h"
#include "Head.h"


CScene::CScene()
	:m_fTimeCount(0)
	,m_pTex(nullptr)
	,m_vResolution (CCore::GetInst()->GetResolution())

	, m_iTileX(0)
	, m_iTileY(0)
{
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

		Safe_Delete_Vec<CObject*>(m_arrObj[i]);
	}
}

void CScene::update()
{
	m_fTimeCount += fDT;

	
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
		// �츮�� Obj�� �����ϱ� ���ؼ���
		// delete obj �� ������ �ܰ��� (update - *render* - event(���⼭ delete))
		// render�ܰ迡�� �����Ͽ��� �Ѵ� (���� ���ϸ� ������ obj�� �����ַ��� �ϰڧc?
		// erase�Լ� �������� iterator�� ����
		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		// erase�� �����ϸ� ���� iter�� ��ȯ�ϱ� ������ ++�� iter�� �� �� ����Ѵ�
		// ���� obj�� alive�����϶� ++���ְ� �ƴҶ� erase���༭ �ݺ��Ѵ�
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

void CScene::SetBodyPos(CObject * _pBody, CObject * _pHead)
{
	switch (CSceneMgr::GetInst()->GetPrevScene()->GetRoomType())
	{
	case ROOM_TYPE::UP:
		_pBody->SetPos(Vec2(m_vResolution.x / 2, LIMITN));
		_pHead->SetPos(Vec2(m_vResolution.x / 2, LIMITN));
		break;
	case ROOM_TYPE::DOWN:
		_pBody->SetPos(Vec2(m_vResolution.x / 2, LIMITS));
		_pHead->SetPos(Vec2(m_vResolution.x / 2, LIMITS));
		break;
	case ROOM_TYPE::LEFT:
		_pBody->SetPos(Vec2(LIMITE, m_vResolution.y / 2));
		_pHead->SetPos(Vec2(LIMITE, m_vResolution.y / 2));
		break;
	case ROOM_TYPE::RIGHT:
		_pBody->SetPos(Vec2(LIMITW, m_vResolution.y / 2));
		_pHead->SetPos(Vec2(LIMITW, m_vResolution.y / 2));
		break;
	}
}



