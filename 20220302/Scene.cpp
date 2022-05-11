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

#include "SelectGDI.h"

#include "WallCollider.h"

#include "Camera.h"



CScene::CScene()
	: m_fTimeCount(0)
	, m_pBgTex(nullptr)
	, m_vResolution (CCore::GetInst()->GetResolution())
	, m_eAdjacencyRoom{}
	, m_roomDir(DIR::END)
	, m_iTileX(0)
	, m_iTileY(0)
{

	CCamera::GetInst()->SetLookAt(m_vResolution / 2.f);
}


CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		// m_arrObj[i]는 여기 소멸자가 호출 될 때 자동으로 vector 소멸자를 부른다
		// 벡터가 CScene의 멤버니까!
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
	vector<CObject*> vecTile = GetGroupObject(GROUP_TYPE::TILE);

	Vec2 vCamLook = CCamera::GetInst()->GetLookAt();
	Vec2 vLeftTop = vCamLook - m_vResolution / 2.f;

	UINT iTileSize = TILE_SIZE;

	// 행렬을 아나 실제로는 타일 idx로 접근해야함
	// 왜냐하면 우리가 2차원으로 선언 안해놨자나
	// idx = (타일 개수 * row) + col
	int iLTCol = static_cast<int>(vLeftTop.x) / iTileSize;
	int iLTRow = static_cast<int>(vLeftTop.y) / iTileSize;
	//int iLTIdx = m_iTileX * iLTRow + iLTCol;

	// 가로 세로에 들어갈 수 있는 최대 타일 개수
	// 끝에 짤리면 +1
	int iClientWidth = (static_cast<int>(m_vResolution.x) / iTileSize);
	int iClientHeight = (static_cast<int>(m_vResolution.y) / iTileSize);

	for (int iCurRow = iLTRow; iCurRow < (iLTRow + iClientHeight); ++iCurRow)
	{
		for (int iCurCol = iLTCol; iCurCol < (iLTCol + iClientWidth); ++iCurCol)
		{
			// 찍으려는 영역엥서 삐져나가면 인덱스 계산 및 렌더를 안함
			if (iCurCol < 0 || iCurCol >= m_iTileX ||
				iCurRow < 0 || iCurRow >= m_iTileY)
			{
				continue;
			}


			// for문 내 타일의 idx 구한것 
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

	// 타일 개수 불러오기
	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	// 개별타일 데이터 불러오기 
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}


	fclose(pFile);
}

void CScene::AddDoor(DIR _eDir)
{
		if (SCENE_TYPE::END != m_eAdjacencyRoom[(UINT)_eDir]);
		{
			CObject* pDoor = new CDoor(_eDir);
			CDoor* pDoorObj = (CDoor*)pDoor;

			switch (_eDir)
			{
			case DIR::E:
				pDoor->SetPos(Vec2(m_vResolution.x - (pDoor->GetScale().x / 2) - 25.f, m_vResolution.y / 2));
				pDoorObj->SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorEW", L"texture\\BackGround\\DoorEW.bmp"));
				pDoorObj->SetSlice(0, 64);
				break;
			case DIR::W:
				pDoor->SetPos(Vec2((pDoor->GetScale().x / 2) + 25.f, m_vResolution.y / 2));
				pDoorObj->SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorEW", L"texture\\BackGround\\DoorEW.bmp"));
				pDoorObj->SetSlice(0, 0);
				break;
			case DIR::S:
				pDoor->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y - (pDoor->GetScale().y / 2) - 25.f));
				pDoorObj->SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorNS", L"texture\\BackGround\\DoorNS.bmp"));
				pDoorObj->SetSlice(0, 48);
				break;
			case DIR::N:
				pDoor->SetPos(Vec2(m_vResolution.x / 2, (pDoor->GetScale().y / 2) + 25.f));
				pDoorObj->SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorNS", L"texture\\BackGround\\DoorNS.bmp"));
				pDoorObj->SetSlice(0, 0);
				break;
			default:
				break;
			}
			pDoor->SetName(L"Door");
			CreateObject(pDoor, GROUP_TYPE::DOOR);
		
		}
}

void CScene::AddWall()
{
	// collider for body
	CObject* pWallColliderN = new CWallCollider(Vec2(640.f, 128.f), Vec2(1000.f, 1.f), DIR::N);
	pWallColliderN->SetName(L"Wall");
	CreateObject(pWallColliderN, GROUP_TYPE::WALL);

	CObject* pWallColliderS = new CWallCollider(Vec2(640.f, 640.f), Vec2(1000.f, 1.f), DIR::S);
	pWallColliderS->SetName(L"Wall");
	CreateObject(pWallColliderS, GROUP_TYPE::WALL);

	CObject* pWallColliderE = new CWallCollider(Vec2(142.f, 389.f), Vec2(1.f, 550.f), DIR::E);
	pWallColliderE->SetName(L"Wall");
	CreateObject(pWallColliderE, GROUP_TYPE::WALL);

	CObject* pWallColliderW = new CWallCollider(Vec2(1138.f, 389.f), Vec2(1.f, 550.f), DIR::W);
	pWallColliderW->SetName(L"Wall");
	CreateObject(pWallColliderW, GROUP_TYPE::WALL);


	// collider for tear
	CObject* pWallTearColliderN = new CWallCollider(Vec2(640.f, 100.f), Vec2(1050.f, 1.f), DIR::N);
	pWallTearColliderN->SetName(L"Wall_Tear");
	CreateObject(pWallTearColliderN, GROUP_TYPE::TEARWALL);

	CObject* pWallTearColliderS = new CWallCollider(Vec2(640.f, 670.f), Vec2(1050.f, 1.f), DIR::S);
	pWallTearColliderS->SetName(L"Wall_Tear");
	CreateObject(pWallTearColliderS, GROUP_TYPE::TEARWALL);

	CObject* pWallTearColliderE = new CWallCollider(Vec2(110.f, 389.f), Vec2(1.f, 600.f), DIR::E);
	pWallTearColliderE->SetName(L"Wall_Tear");
	CreateObject(pWallTearColliderE, GROUP_TYPE::TEARWALL);

	CObject* pWallTearColliderW = new CWallCollider(Vec2(1170.f, 389.f), Vec2(1.f, 600.f), DIR::W);
	pWallTearColliderW->SetName(L"Wall_Tear");
	CreateObject(pWallTearColliderW, GROUP_TYPE::TEARWALL);

}

void CScene::SetPlayerPos(CObject * _pPlayer)
{
	switch (CSceneMgr::GetInst()->GetPrevScene()->GetRoomDir ())
	{
	case DIR::S:
		_pPlayer->SetPos(Vec2(m_vResolution.x / 2, LIMITN+100.f));		
		break;
	case DIR::N:
		_pPlayer->SetPos(Vec2(m_vResolution.x / 2, LIMITS-100.f));
		break;
	case DIR::W:
		_pPlayer->SetPos(Vec2(LIMITE, m_vResolution.y / 2));
		break;
	case DIR::E:
		_pPlayer->SetPos(Vec2(LIMITW, m_vResolution.y / 2));
		break;	
	case DIR::END:
		_pPlayer->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));
		break;

	}
}




