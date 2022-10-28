#include "pch.h"
#include "Map.h"

#include "PathMgr.h"
#include "SceneMgr.h"

#include "Scene.h"

#include "Room.h"
#include "Core.h"

#include "StartRoom.h"
#include "NormalRoom.h"
#include "TreasureRoom.h"

CMap::CMap()
	: m_MapData{}
{
}

CMap::~CMap()
{

}

void CMap::LoadMap(const wstring& _strRelativePath)
{

		wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
		strFilePath += _strRelativePath;

		FILE* pFile = nullptr;

		_wfopen_s(&pFile, strFilePath.c_str(), L"rt,ccs=UTF-8");

		assert(pFile);

		// 맵 정보 읽기
//		wchar_t mapdata[7] = L"";
		wchar_t buff[64] = L"";


		if (0 != pFile)
		{
			Vec2 vResolution = CCore::GetInst()->GetResolution();
			for (int y = 0; y < MAP_SIZE; y++)
			{
				fgetws(buff, 63, pFile);
				for (int x = 0; x < MAP_SIZE; x++)
				{
					switch (buff[x])
					{
					case L'0':	
						break;
					case L'1':
						m_MapData[y][x] = new CStartRoom();
						m_vStartPos = Vec2(x * vResolution.x + (vResolution.x / 2), y * vResolution.y + (vResolution.y / 2));
						SetCurrentRoom(dynamic_cast<CRoom*>(m_MapData[y][x]));
						m_pPrevRoom = dynamic_cast<CRoom*>(m_MapData[y][x]);
						break;
					case L'2':
						m_MapData[y][x] = new CNormalRoom();
						break;
					case L'3':
						m_MapData[y][x] = new CTreasureRoom();
						break;
					case L'9':
						//m_MapData[y][x] = new CRoom(ROOM_TYPE::BOSS, Vec2(x, y), this);
						//break;
					default:
						break;
					}
					// 방 좌표 주고 map과 연결
					if (nullptr != m_MapData[y][x])
					{
						dynamic_cast<CRoom*>(m_MapData[y][x])->SetRoomPos(Vec2(x, y));
						dynamic_cast<CRoom*>(m_MapData[y][x])->SetOwner(this);
					}
				}
			}
			// 불러온 map init
			for (int y = 0; y < MAP_SIZE; y++)
			{
				for (int x = 0; x < MAP_SIZE; x++)
				{
					if (nullptr != m_MapData[y][x])
					{
						m_MapData[y][x]->SetScale(vResolution);
						m_MapData[y][x]->SetPos(Vec2(x * vResolution.x + (vResolution.x / 2), y * vResolution.y + (vResolution.y / 2)));
						dynamic_cast<CRoom*>(m_MapData[y][x])->AddWall();
						dynamic_cast<CRoom*>(m_MapData[y][x])->AddDoor();
						CSceneMgr::GetInst()->GetCurScene()->AddObject(m_MapData[y][x], GROUP_TYPE::ROOM);
					}
				}
			}
			fclose(pFile);
		}


		CSceneMgr::GetInst()->GetCurScene()->SetMap(this);
	
}
