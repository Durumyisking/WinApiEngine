#include "pch.h"
#include "Scene.h"

#include "Core.h"
#include "Object.h"
#include "Texture.h"
#include "Tile.h"
#include "Body.h"
#include "Head.h"
#include "Door.h"

#include "SceneMgr.h"
#include "ResMgr.h"
#include "TimeMgr.h"
#include "PathMgr.h"
#include "Collider.h"

#include "SelectGDI.h"

#include "WallCollider.h"



CScene::CScene()
	: m_fTimeCount(0)
	, m_pTex(nullptr)
	, m_vResolution (CCore::GetInst()->GetResolution())
	, m_eAdjacencyRoom{}
	, m_roomDir(DIR::END)
	, m_iTileX(0)
	, m_iTileY(0)
{

	CObject* pWallColliderN = new CWallCollider(Vec2(640.f, 128.f), Vec2(300.f, 1.f), DIR::N);
	pWallColliderN->SetName(L"Wall");
	CreateObject(pWallColliderN, GROUP_TYPE::WALL);

	CObject* pWallColliderS = new CWallCollider(Vec2(640.f, 640.f), Vec2(300.f, 1.f),DIR::S);
	pWallColliderS->SetName(L"Wall");
	CreateObject(pWallColliderS, GROUP_TYPE::WALL);

	CObject* pWallColliderE = new CWallCollider(Vec2(142.f, 389.f), Vec2(1.f, 400.f), DIR::E);
	pWallColliderE->SetName(L"Wall");
	CreateObject(pWallColliderE, GROUP_TYPE::WALL);

	CObject* pWallColliderW = new CWallCollider(Vec2(1138.f, 389.f), Vec2(1.f, 400.f), DIR::W);
	pWallColliderW->SetName(L"Wall");
	CreateObject(pWallColliderW, GROUP_TYPE::WALL);
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
	CSelectGDI pen(_dc, PEN_TYPE::GREEN);
	CSelectGDI brush(_dc, BRUSH_TYPE::HOLLOW);

	//Rectangle(_dc, 142, 128, 1138, 640);
//	Rectangle(_dc, 0, 0, static_cast<int>(m_vResolution.x), static_cast<int>(m_vResolution.y));


	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		// 우리가 Obj를 삭제하기 위해서는
		// delete obj 전 마지막 단계인 (update - *render* - event(여기서 delete))
		// render단계에서 삭제하여야 한다 (삭제 안하면 삭제한 obj를 보여주려고 하겠쬬?
		// erase함수 쓰기위해 iterator로 선언
		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		// erase로 삭제하면 다음 iter을 반환하기 때문에 ++시 iter가 두 번 상승한다
		// 따라서 obj가 alive상태일때 ++해주고 아닐땐 erase해줘서 반복한다
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




