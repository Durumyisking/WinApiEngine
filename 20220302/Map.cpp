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
#include "BossRoom.h"
#include "EvilRoom.h"

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
						dynamic_cast<CRoom*>(m_MapData[y][x])->SetType(ROOM_TYPE::START);
						break;
					case L'2':
						m_MapData[y][x] = new CNormalRoom();
						dynamic_cast<CRoom*>(m_MapData[y][x])->SetType(ROOM_TYPE::NORMAL);
						break;
					case L'3':
						m_MapData[y][x] = new CTreasureRoom();
						dynamic_cast<CRoom*>(m_MapData[y][x])->SetType(ROOM_TYPE::TRESURE);
						break;
					case L'8':
						m_MapData[y][x] = new CEvilRoom();
						dynamic_cast<CRoom*>(m_MapData[y][x])->SetType(ROOM_TYPE::EVIL);
						break;
					case L'9':
						m_MapData[y][x] = new CBossRoom();
						dynamic_cast<CRoom*>(m_MapData[y][x])->SetType(ROOM_TYPE::BOSS);
						break;
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
						ROOM_TYPE RoomType = dynamic_cast<CRoom*>(m_MapData[y][x])->GetType();
						switch (RoomType)
						{
						case ROOM_TYPE::NORMAL:
							dynamic_cast<CRoom*>(m_MapData[y][x])->LoadRoom(ROOM_TYPE::NORMAL);
							break;
						case ROOM_TYPE::TRESURE:
							dynamic_cast<CRoom*>(m_MapData[y][x])->LoadRoom(ROOM_TYPE::TRESURE);
							break;
						case ROOM_TYPE::BOSS:
							dynamic_cast<CRoom*>(m_MapData[y][x])->LoadRoom(ROOM_TYPE::BOSS);
							break;
						case ROOM_TYPE::EVIL:
							dynamic_cast<CRoom*>(m_MapData[y][x])->LoadRoom(ROOM_TYPE::EVIL);
							break;
						default:
							break;
						}

						CSceneMgr::GetInst()->GetCurScene()->AddObject(m_MapData[y][x], GROUP_TYPE::ROOM);
					}
				}
			}
			fclose(pFile);
		}


		CSceneMgr::GetInst()->GetCurScene()->SetMap(this);
	
}
