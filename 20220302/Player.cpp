#include "pch.h"
#include "Player.h"
#include "Monster.h"
#include"Missile.h"
#include "Door.h"
#include "Scene.h"
#include "Collider.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Animation.h"
#include "Item.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ResMgr.h"

#include "Body.h"
#include "Head.h"

#include "WallCollider.h"
#include "Heart.h"
#include "Pickup.h"
#include "PickupHeart.h"

#include "Door.h"
#include "Room.h"
#include "Map.h"


CPlayer::CPlayer()
	: m_dAttackDealy(fDT)
	, m_pAnim(nullptr)
	, m_pOwner(nullptr)
	, m_pTex(nullptr)
	, m_pStat(nullptr)
	, m_Pickup{}
	, m_finvincibilityTime(1.0f)
	, m_arrCollider{}
	, m_bFramePass(false)
	, m_vPrevPos()
	, m_bCollisionwall(false)
{
	m_Stat = { 6, 6, 5, 400.f, 450.f, 2.f ,0.38f };
	m_pStat = &m_Stat;

	m_strAnimName = L"Hurt";
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player\\isaac.bmp");

	CreateRigidBody();
	GetRigidBody()->SetMaxVelocity(m_pStat->m_fSpeed);
	
	
}


CPlayer::~CPlayer()
{
	//if (nullptr == pBody && nullptr == pHead)
	//{
	//	delete this;
	//}

	m_pCostume.clear();
}


void CPlayer::update()
{
	// 추후 죽음처리 해야합니다///
	if (0 >= m_pStat->m_iHP)
		m_pStat->m_iHP = 0;

	// 공격 쿨타임
	m_dAttackDealy += fDT;

	// 무적시간
	if (m_finvincibilityTime < 1.0f)
		m_finvincibilityTime += fDT;


	// 이동
	CRigidBody* pRigid = GetRigidBody();

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	float fTemp = m_Stat.m_fSpeed / 8.f;

	if (KEY_HOLD(KEY::W)) {
		pRigid->AddVelocity(Vec2(0.f, -fTemp));
		pRigid->AddForce(Vec2(0.f, -200.f));
	}
	if (KEY_HOLD(KEY::S)) {
		pRigid->AddVelocity(Vec2(0.f, fTemp));
		pRigid->AddForce(Vec2(0.f, 200.f));
	}
	if (KEY_HOLD(KEY::A)) {
		pRigid->AddVelocity(Vec2(-fTemp, 0.f));
		pRigid->AddForce(Vec2(-200.f, 0.f));
	}
	if (KEY_HOLD(KEY::D)) {
		pRigid->AddVelocity(Vec2(fTemp, 0.f));
		pRigid->AddForce(Vec2(200.f, 0.f));
	}

	if (!(KEY_HOLD(KEY::W)) && !(KEY_HOLD(KEY::S)) &&
		!(KEY_HOLD(KEY::A)) && !(KEY_HOLD(KEY::D)))
	{
	}

	if (m_bCollisionwall)
	{
		//pRigid->SetVelocity(Vec2(0.f, 0.f));
		//pRigid->SetForce(Vec2(0.f, 0.f));
		//vPos = GetPrevPos();

		

		m_bCollisionwall = false;
	}
	//else
	//{
		SetPrevPos();
//	}
	SetPos(vPos);
	// 부모객체만 자식들 setpos
	if (nullptr != pBody && nullptr != pHead)
	{
		pBody->SetPos(vPos);
		pHead->SetPos(vPos);
	}


	for (size_t i = 0; i < m_pCostume.size(); i++)
	{
		if (nullptr != m_pCostume[i])
			m_pCostume[i]->update();
	}

	// 보유 아이템 체크 얻은 아이템이 있으면 itemcheck에서 획득처리
	if (nullptr != m_GetItemCheck)
	{
		ItemCheck();
		m_GetItemCheck = nullptr;
	}


}

void CPlayer::render(HDC _dc)
{
	// 무적시간 동안 프레임마다 깜빡이게 합니다.
	if (m_finvincibilityTime < 1.0f)
	{
		if (m_bFramePass)
		{
			// 깜빡임 토글 true일때 렌더링 X
			m_bFramePass = false;
			return;
		}
		else
		{
			// false일때는 렌더링하러 내려감
			m_bFramePass = true;
		}
	}
	
	// body와 head는
	if (nullptr != m_pOwner)
	{
		// 부모의 hurt가 진행중이면 렌더링 하지 않는다
		if (L"Hurt" == m_pOwner->GetAnimator()->GetCurAnim()->GetName() && !m_pOwner->GetAnimator()->GetCurAnim()->IsFinish())
		{
			return;
		}
		else
		{
			for (size_t i = 0; i < m_pCostume.size(); i++)
			{
				if (nullptr != m_pCostume[i])
					m_pCostume[i]->render(_dc);
			}
			component_render(_dc);
		}
	}
	// 부모는 무적권 렌더링
	else
	{

		//for (size_t i = 0; i < m_pCostume.size(); i++)
		//{
		//	if (nullptr != m_pCostume[i])
		//		m_pCostume[i]->render(_dc);
		//}
		component_render(_dc);
	}
	
}




CBody* CPlayer::Body()
{
	if (nullptr == m_pOwner)
		return pBody;

	return nullptr;
}

CHead* CPlayer::Head()
{
	if (nullptr == m_pOwner)
		return pHead;

	return nullptr;
}

void CPlayer::init()
{
	SetScale(Vec2(138.f, 91.f));

	// 플레이어의 상하좌우 충돌체 // 이동을 막기 위함입니다.
	//for (UINT i = static_cast<UINT>(DIR::N); i < static_cast<UINT>(DIR::END); i++)
	//{
	//	m_arrCollider[i] = new CCollider;
	//	m_arrCollider[i]->SetOwner(dynamic_cast<CObject*>(this));
	//	m_arrCollider
	//}


	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 45.f));
	GetCollider()->SetScale(Vec2(40.f, 30.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Hurt", m_pTex, Vec2(0.f, 325.f), Vec2(48.f, 37.f), Vec2(65.f, 0.f), 0.5f, 2, false);

	
	pBody = new CBody;
	pHead = new CHead;
	
	pBody->SetOwner(this);
	pHead->SetOwner(this);

	pBody->SetName(L"Body");
	pHead->SetName(L"Head");

	pBody->SetStat(m_pStat);
	pHead->SetStat(m_pStat);

	pBody->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));
	pHead->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));


	m_Pickup.SetBomb(9);

	CreateObject(pBody, GROUP_TYPE::PLAYER);
	CreateObject(pHead, GROUP_TYPE::PLAYER);

}

void CPlayer::OnCollision(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	// monster
	if (L"Monster" == pOtherObj->GetName() || L"Tear_Monster" == pOtherObj->GetName())
	{
//		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f));



		CMonster* pMonster = dynamic_cast<CMonster*>(pOtherObj);

		if (m_finvincibilityTime >= 1.0f)
		{
			if (GetAnimator()->GetCurAnim()->IsFinish())
			{
				GetAnimator()->GetCurAnim()->SetFrame(0);
			}
			PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), false);

			m_finvincibilityTime = 0;
			// hurt 애니메이션 재생
			m_iPrevHp = m_pStat->m_iHP;
			--m_pStat->m_iHP;

		}
	}

	if (L"PickupHeart" == pOtherObj->GetName())
	{
		CPickupHeart* pHeart = dynamic_cast<CPickupHeart*>(pOtherObj);

		Vec2 vec = this->GetPos() - pHeart->GetPos();
		vec.Normalize();
		float _f = pHeart->GetRigidBody()->GetVelocity().Length();
		vec = vec * 50.f;
		this->GetRigidBody()->AddForce(vec);
	}


	if (L"Explode" == pOtherObj->GetName())
	{
		Vec2 vDir = pOtherObj->GetPos() - GetPos();
		vDir.Normalize();
		vDir = vDir * 500.f;
		Vec2 vResult = GetRigidBody()->GetVelocity() - vDir;
		GetRigidBody()->SetVelocity(vResult);
	}

	if (L"Wall" == pOtherObj->GetName())
	{
		m_bCollisionwall = true;
	}

}

void CPlayer::OnCollisionEnter(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	// doord
	if (L"Door" == pOtherObj->GetName())
	{
		CDoor* pdoor = dynamic_cast<CDoor*>(pOtherObj);
		Vec2 vPos = {};

		if (pdoor->IsOpen())
		{
			switch (pdoor->Dir())
			{
			case DIR::N:
				// 문 뒤에있는 방의 위치를 얻어 그 방으로 이동합니다.
				vPos = Vec2(pdoor->GetOwner()->GetRoomPos().x, pdoor->GetOwner()->GetRoomPos().y - 1);
				SetPos(vPos * m_vResolution + (m_vResolution / 2) - Vec2(0.f, -225.f));
				CCamera::GetInst()->SetLookAt(vPos * m_vResolution + (m_vResolution / 2));
				// 들어간 방을 현재 방으로 설정합니다.
				dynamic_cast<CRoom*>(pdoor->GetOwner()->GetOwner()->GetMapData(static_cast<int>(pdoor->GetOwner()->GetRoomPos().y - 1), static_cast<int>(pdoor->GetOwner()->GetRoomPos().x)))->Enter();
				break;
			case DIR::S:
				vPos = Vec2(pdoor->GetOwner()->GetRoomPos().x, pdoor->GetOwner()->GetRoomPos().y + 1);
				SetPos(vPos * m_vResolution + (m_vResolution / 2) - Vec2(0.f, 275.f));
				CCamera::GetInst()->SetLookAt(vPos * m_vResolution + (m_vResolution / 2));
				dynamic_cast<CRoom*>(pdoor->GetOwner()->GetOwner()->GetMapData(static_cast<int>(pdoor->GetOwner()->GetRoomPos().y + 1), static_cast<int>(pdoor->GetOwner()->GetRoomPos().x)))->Enter();
				break;
			case DIR::E:
				vPos = Vec2(pdoor->GetOwner()->GetRoomPos().x + 1, pdoor->GetOwner()->GetRoomPos().y);
				SetPos(vPos * m_vResolution + (m_vResolution / 2) - Vec2(500.f, 40.f));
				CCamera::GetInst()->SetLookAt(vPos * m_vResolution + (m_vResolution / 2));
				dynamic_cast<CRoom*>(pdoor->GetOwner()->GetOwner()->GetMapData(static_cast<int>(pdoor->GetOwner()->GetRoomPos().y), static_cast<int>(pdoor->GetOwner()->GetRoomPos().x + 1)))->Enter();
				break;
			case DIR::W:
				vPos = Vec2(pdoor->GetOwner()->GetRoomPos().x - 1, pdoor->GetOwner()->GetRoomPos().y);
				SetPos(vPos * m_vResolution + (m_vResolution / 2) - Vec2(-500.f, 40.f));
				CCamera::GetInst()->SetLookAt(vPos * m_vResolution + (m_vResolution / 2));
				dynamic_cast<CRoom*>(pdoor->GetOwner()->GetOwner()->GetMapData(static_cast<int>(pdoor->GetOwner()->GetRoomPos().y), static_cast<int>(pdoor->GetOwner()->GetRoomPos().x - 1)))->Enter();
				break;
			default:
				break;
			}
		}
		else
		{
			// 플레이어의 이동을 막습니다.
			CRigidBody* pRigid = GetRigidBody();
			Vec2 vDir = pRigid->GetVelocity().Normalize();
			Vec2 vtemp = (-vDir * (_pOther->GetScale() / 2)) + (-vDir * (GetCollider()->GetScale() / 2));
			//    역벡터  *  적 충돌체스케일 / 2        +   역벡터   *    자기 충돌체 스케일 / 2
			vDir = GetCollider()->GetFinalPos() - GetCollider()->GetOffsetPos() + vtemp;


			SetPos(vDir);

		}
	}

	// wall
	if (L"Wall" == pOtherObj->GetName())
	{
		//m_bCollisionwall = true;
		/*
		충돌체 위치 + 역벡터 * (적 충돌체 스케일 / 2) + 역벡터 * (자기 충돌체 스케일 / 2)
		*/
		CRigidBody* pRigid = GetRigidBody();
		Vec2 vDir = pRigid->GetVelocity().Normalize();
		Vec2 vtemp = (-vDir * (_pOther->GetScale() / 2)) + (-vDir * (GetCollider()->GetScale() / 2));
				//    역벡터  *  적 충돌체스케일 / 2        +   역벡터   *    자기 충돌체 스케일 / 2
		vDir = GetCollider()->GetFinalPos() - GetCollider()->GetOffsetPos() + vtemp;

		
		SetPos(vDir);

	}
	
	// item
	if (L"Item" == pOtherObj->GetName())
	{
		CItem* pItem = dynamic_cast<CItem*>(pOtherObj);
		++(m_vInventory[static_cast<UINT>(pItem->GetItemName())]);
		m_GetItemCheck = pItem;


	}	

	if (L"PickupHeart" == pOtherObj->GetName())
	{
		CPickupHeart* pHeart = dynamic_cast<CPickupHeart*>(pOtherObj);

		Vec2 vec = this->GetPos() - pHeart->GetPos();
		vec.Normalize();
		float _f = pHeart->GetRigidBody()->GetVelocity().Length();
		vec = vec  * 50.f;
		this->GetRigidBody()->AddForce(vec);
	}

	if (L"Explode" == pOtherObj->GetName())
	{
		Vec2 vDir = pOtherObj->GetPos() - GetPos();
		vDir.Normalize();
		vDir = vDir * 500.f;
		Vec2 vResult = GetRigidBody()->GetVelocity() - vDir;
		GetRigidBody()->SetVelocity(vResult);
	}

	if (L"Monster" == pOtherObj->GetName() || L"Tear_Monster" == pOtherObj->GetName())
	{
		Vec2 vDir = pOtherObj->GetPos() - GetPos();
		vDir.Normalize();
		vDir = vDir * 500.f;
		Vec2 vResult = GetRigidBody()->GetVelocity() - vDir;
		GetRigidBody()->SetVelocity(vResult);

		if(GetAnimator()->GetCurAnim() != GetAnimator()->FindAnimation(L"Hurt"))
		{
			if (GetAnimator()->GetCurAnim()->IsFinish())
			{
				GetAnimator()->GetCurAnim()->SetFrame(0);
			}

			PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), false);

			m_finvincibilityTime = 0;
			m_iPrevHp = m_pStat->m_iHP;
			--m_pStat->m_iHP;

		}


	}
}

void CPlayer::OnCollisionExit(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	
	// wall
	if (L"Wall" == pOtherObj->GetName())
	{
		
	}
}

void CPlayer::CreateMissile(Vec2 _vDir)
{


}

void CPlayer::ItemCheck()
{
	float fFricCoeffRatio = GetRigidBody()->GetFricCoeff() / m_pStat->m_fSpeed;

	*m_pStat += m_GetItemCheck->GetStat();

	pBody->SetStat(this->m_pStat);
	pHead->SetStat(this->m_pStat);
		
	GetRigidBody()->SetMaxVelocity(m_pStat->m_fSpeed);
	GetRigidBody()->SetFricCoeff(fFricCoeffRatio * m_pStat->m_fSpeed);

	if (ITEM_TABLE::lunch == m_GetItemCheck->GetItemName())
	{
		m_bGetHpMax = true;
	}
	CCostume* pCosTemp = new CCostume(m_GetItemCheck->GetItemName());
	// 이미 있는 아이템이면 코스튬추가 필요없음
	for (size_t i = 0; i < m_pCostume.size(); i++)
	{
		if (m_pCostume[i]->GetItemName() == pCosTemp->GetItemName())
		{
			return;
		}
	}
	// 코스튬이 있는 아이템일때만
	if (ITEM_TABLE::end != pCosTemp->GetItemName())
	{
		pCosTemp->SetPlayer(this);
		CreateObject(pCosTemp, GROUP_TYPE::COSTUME);
		m_pCostume.push_back(pCosTemp);
	}
}

