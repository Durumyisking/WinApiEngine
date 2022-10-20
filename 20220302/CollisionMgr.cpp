#include "pch.h"
#include "CollisionMgr.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Collider.h"
#include "Object.h"


/*
UNION


*/

struct sTest
{
	// 8바이트
	int a;
	float f;
};

union Test
{
	// 4바이트
	// 제일 큰 size기준으로 같은 공간을 공유한다.
	// 같은 공간내에 어떤 변수를 선언하느냐에 따라 그에 맞춘 자료형으로 본다.
	int a;
	float f;	
};



CCollisionMgr::CCollisionMgr()
{	
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::init()
{
}

void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol)) // 실제로 충돌이 일어났는지 매 update때 확인!
			{
				CollisionGroupupdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CollisionGroupupdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	
	// 여기도 const ref로 받아야 우리가 pCurScene의 objgroup 을 받아옴
	const vector <CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector <CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	// 이전 프레임의 충돌 정보 저장할 곳
	map <ULONGLONG, bool>::iterator iter;


	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// 충돌체 보유 X
		if (nullptr == vecLeft[i]->GetCollider())
		{
			continue;
		}

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// 충돌체 보유X || 자기 자신과의 충돌
			if (nullptr == vecRight[j]->GetCollider() ||
				vecLeft[i] == vecRight[j])
			{
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			COLLIDER_ID ID;
 			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);

			// 찾는값 즉 키ID의 이전의 충돌정보가 없다 (첫 충돌 정보거나, 이전 프레임에 충돌한적 없다)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));	// 이전 프레임에 충돌 정보 없으니까 false
				iter = m_mapColInfo.find(ID.ID);				// 이번 충돌의 충돌 정보 가리킴
			}

			if (IsCollision(pLeftCol, pRightCol))
			{
				// 현재 충돌 중이다.
				
				if (iter->second)
				{
					// 이전에도 충돌 하고 있었다.
					
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{	
						// 둘 중 하나가 삭제 예정이면 충돌 해제
						vecLeft[i]->GetCollider()->OnCollisionExit(pRightCol);
						vecRight[j]->GetCollider()->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						// vecleft와 vecright가 충돌중이라는 정보 전달
						vecLeft[i]->GetCollider()->OnCollision(pRightCol);
						vecRight[j]->GetCollider()->OnCollision(pLeftCol);
					}
				}
				else
				{
					// 이전에 충돌하지 않았다.
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						// 둘 중 하나가 삭제 예정이면 충돌은 안한걸로 취급한다
						vecLeft[i]->GetCollider()->OnCollisionEnter(pRightCol);
						vecRight[j]->GetCollider()->OnCollisionEnter(pLeftCol);
						iter->second = true;

					}

				}

			}
			else
			{
				// 현재 충돌중이지 않다.
				if (iter->second)
				{
					// 이전에는 충돌하고 있었다 = 충돌체가 막 벗어나진 시점
					vecLeft[i]->GetCollider()->OnCollisionExit(pRightCol);
					vecRight[j]->GetCollider()->OnCollisionExit(pLeftCol);
					iter->second = false;

				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider * pLeftCol, CCollider * pRightCol)
{
	// 충돌체의 이동이 전부 끝나고 충돌을 검사하는 부분 => 충돌체들의 최종 위치를 가져와야서 겹친 부분이 있나 확인해야함

	Vec2 vLeftPos = pLeftCol->GetFinalPos();
	Vec2 vLeftScale = pLeftCol->GetScale();
	
	Vec2 vRightPos = pRightCol->GetFinalPos();
	Vec2 vRightScale = pRightCol->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}


void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값의 그룹 타입을 행으로,
	// 큰 값을 열(비트)로 사용 

	UINT	iRow = (UINT)_eLeft;
	UINT	iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
		m_arrCheck[iRow] &= ~(1 << iCol);	
	else
		m_arrCheck[iRow] |= (1 << iCol);
	
}



