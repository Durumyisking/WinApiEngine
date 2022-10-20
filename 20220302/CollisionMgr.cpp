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
	// 8����Ʈ
	int a;
	float f;
};

union Test
{
	// 4����Ʈ
	// ���� ū size�������� ���� ������ �����Ѵ�.
	// ���� �������� � ������ �����ϴ��Ŀ� ���� �׿� ���� �ڷ������� ����.
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
			if (m_arrCheck[iRow] & (1 << iCol)) // ������ �浹�� �Ͼ���� �� update�� Ȯ��!
			{
				CollisionGroupupdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CollisionGroupupdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	
	// ���⵵ const ref�� �޾ƾ� �츮�� pCurScene�� objgroup �� �޾ƿ�
	const vector <CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector <CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	// ���� �������� �浹 ���� ������ ��
	map <ULONGLONG, bool>::iterator iter;


	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// �浹ü ���� X
		if (nullptr == vecLeft[i]->GetCollider())
		{
			continue;
		}

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// �浹ü ����X || �ڱ� �ڽŰ��� �浹
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

			// ã�°� �� ŰID�� ������ �浹������ ���� (ù �浹 �����ų�, ���� �����ӿ� �浹���� ����)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));	// ���� �����ӿ� �浹 ���� �����ϱ� false
				iter = m_mapColInfo.find(ID.ID);				// �̹� �浹�� �浹 ���� ����Ŵ
			}

			if (IsCollision(pLeftCol, pRightCol))
			{
				// ���� �浹 ���̴�.
				
				if (iter->second)
				{
					// �������� �浹 �ϰ� �־���.
					
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{	
						// �� �� �ϳ��� ���� �����̸� �浹 ����
						vecLeft[i]->GetCollider()->OnCollisionExit(pRightCol);
						vecRight[j]->GetCollider()->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						// vecleft�� vecright�� �浹���̶�� ���� ����
						vecLeft[i]->GetCollider()->OnCollision(pRightCol);
						vecRight[j]->GetCollider()->OnCollision(pLeftCol);
					}
				}
				else
				{
					// ������ �浹���� �ʾҴ�.
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						// �� �� �ϳ��� ���� �����̸� �浹�� ���Ѱɷ� ����Ѵ�
						vecLeft[i]->GetCollider()->OnCollisionEnter(pRightCol);
						vecRight[j]->GetCollider()->OnCollisionEnter(pLeftCol);
						iter->second = true;

					}

				}

			}
			else
			{
				// ���� �浹������ �ʴ�.
				if (iter->second)
				{
					// �������� �浹�ϰ� �־��� = �浹ü�� �� ����� ����
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
	// �浹ü�� �̵��� ���� ������ �浹�� �˻��ϴ� �κ� => �浹ü���� ���� ��ġ�� �����;߼� ��ģ �κ��� �ֳ� Ȯ���ؾ���

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
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ)�� ��� 

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



