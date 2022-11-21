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

#include "BossRoom.h"


CPlayer::CPlayer()
	: m_dAttackDealy(fDT)
	, m_pAnim(nullptr)
	, m_pOwner(nullptr)
	, m_pTex(nullptr)
	, m_pStat(nullptr)
	, m_Pickup{}
	, m_finvincibilityTime(1.0f)
	, m_bFramePass(false)
	, m_vPrevPos()
	, m_arrWallDirCheck()
	, m_bGoTrapdoor(false)
	, m_bStateClear(false)
	, m_bClearAnimTimer(0.f)
	, m_bIsWafer(false)
	, m_pItemTex(nullptr)
{
	m_Stat = { 6, 6, 5, 400.f, 600.f, 1.5f ,0.38f };
	m_pStat = &m_Stat;

	m_bIsPlayer = true;

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
	// 추후 죽음처리 해야합니다/
	if (0 >= m_pStat->m_iHP)
		m_pStat->m_iHP = 0;

	// 트랩도어 애니메이션
	if (m_bGoTrapdoor)
	{
		StartTrapdoorAnim();
	}

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

	//if(GetRigidBody()->GetVelocity().IsZero())
	//	m_MoveFlag = 0;
	
	if (KEY_HOLD(KEY::W)) {
		if (!m_arrWallDirCheck[static_cast<UINT>(DIR::UP)])
		{
			pRigid->AddVelocity(Vec2(0.f, -fTemp));
			pRigid->AddForce(Vec2(0.f, -200.f));
			m_MoveFlag |= static_cast<UINT>(MOVE_FLAG::UP);
			m_LastMoveFlag = m_MoveFlag;
		}
	}
	if (KEY_HOLD(KEY::S)) {
		if (!m_arrWallDirCheck[static_cast<UINT>(DIR::DOWN)])
		{
			pRigid->AddVelocity(Vec2(0.f, fTemp));
			pRigid->AddForce(Vec2(0.f, 200.f));
			m_MoveFlag |= static_cast<UINT>(MOVE_FLAG::DOWN);
			m_LastMoveFlag = m_MoveFlag;
		}
	}
	if (KEY_HOLD(KEY::A)) {
		if (!m_arrWallDirCheck[static_cast<UINT>(DIR::LEFT)])
		{
			pRigid->AddVelocity(Vec2(-fTemp, 0.f));
			pRigid->AddForce(Vec2(-200.f, 0.f));
			m_MoveFlag |= static_cast<UINT>(MOVE_FLAG::LEFT);
			m_LastMoveFlag = m_MoveFlag;
		}
	}
	if (KEY_HOLD(KEY::D)) {
		if (!m_arrWallDirCheck[static_cast<UINT>(DIR::RIGHT)])
		{
			pRigid->AddVelocity(Vec2(fTemp, 0.f));
			pRigid->AddForce(Vec2(200.f, 0.f));
			m_MoveFlag |= static_cast<UINT>(MOVE_FLAG::RIGHT);
			m_LastMoveFlag = m_MoveFlag;
		}
	}

	SetPos(vPos);


	// 부모객체만 자식들 setpos
	if (nullptr != pBody && nullptr != pHead)
	{
		pBody->SetPos(vPos);
		pHead->SetPos(vPos);
	}

	if (m_bcoll)
	{
		Vec2 vTemp = IntersectArea(m_pCollobj);
		SetPos(GetPos() - vTemp);
		m_bcoll = false;
	}


	if (!(KEY_HOLD(KEY::W)) && !(KEY_HOLD(KEY::S)) &&
		!(KEY_HOLD(KEY::A)) && !(KEY_HOLD(KEY::D)))
	{
	}


	if (KEY_AWAY(KEY::W)) 
			m_MoveFlag ^= static_cast<UINT>(MOVE_FLAG::UP);
	if (KEY_AWAY(KEY::S))
			m_MoveFlag ^= static_cast<UINT>(MOVE_FLAG::DOWN);
	if (KEY_AWAY(KEY::A))
			m_MoveFlag ^= static_cast<UINT>(MOVE_FLAG::LEFT);
	if (KEY_AWAY(KEY::D)) 
			m_MoveFlag ^= static_cast<UINT>(MOVE_FLAG::RIGHT);

	

	for (size_t i = 0; i < m_pCostume.size(); i++)
	{
		if (nullptr != m_pCostume[i])
			m_pCostume[i]->update();
	}

	//// 보유 아이템 체크 얻은 아이템이 있으면 itemcheck에서 획득처리
	//if (nullptr != m_GetItemCheck)
	//{
	//	ItemCheck();
	//	//m_GetItemCheck = nullptr;
	//}


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
		// 부모의 애니메이션이 진행중이면 렌더링 하지 않는다
			if (L"Hurt" == m_pOwner->GetAnimator()->GetCurAnim()->GetName() && !m_pOwner->GetAnimator()->GetCurAnim()->IsFinish()
				|| L"Jump" == m_pOwner->GetAnimator()->GetCurAnim()->GetName() && !m_pOwner->GetAnimator()->GetCurAnim()->IsFinish()
				|| L"GetItem" == m_pOwner->GetAnimator()->GetCurAnim()->GetName() && !m_pOwner->GetAnimator()->GetCurAnim()->IsFinish())
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
		component_render(_dc);
	}

	// 부모 애니메이션 리셋
	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		if (GetAnimator()->GetCurAnim() == GetAnimator()->FindAnimation(L"GetItem"))
			m_pItemTex = nullptr;
		GetAnimator()->ResetCurAnim();

	}

	// 아이템을 획득했을때
	if (GetAnimator()->GetCurAnim() == GetAnimator()->FindAnimation(L"GetItem"))
	{
		Vec2 vPos = GetPos() - Vec2(0.f, 40.f);

		// 카메라 시점 동기화
		vPos = CCamera::GetInst()->GetRenderPos(vPos);

		TransparentBlt(_dc
			, static_cast<int>(vPos.x - (64.f / 2.f))
			, static_cast<int>(vPos.y - (64.f / 2.f))
			, 64, 64
			, m_pItemTex->GetDC()
			, 0, 0, 32, 32
			, RGB(255, 0, 255));

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

void CPlayer::AnimOper()
{
	PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), false);

	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		GetAnimator()->GetCurAnim()->SetFrame(0);
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), false);

	}
}

void CPlayer::StartTrapdoorAnim()
{
	m_bClearAnimTimer += fDT;

	Vec2 vPos = dynamic_cast<CBossRoom*>(CSceneMgr::GetInst()->GetCurScene()->GetMap()->GetCurrentRoom())->m_pTrapdoor->GetPos();
	if (m_bClearAnimTimer <= 0.5f)
	{
		vPos.y -= 120.f;
	}
	else if (m_bClearAnimTimer > 0.5f && m_bClearAnimTimer <= 1.f)
	{
		vPos.y -= 50.f;
		Vec2 vOffset = GetAnimator()->GetCurAnim()->GetOffset();

		//if (GetAnimator()->GetCurAnim()->GetMagnify() > 1.f)
		//{
		//	vOffset.x += fDT * 725.f;
		//	vOffset.y += fDT * 725.f;
		//	GetAnimator()->GetCurAnim()->SetOffset(vOffset);
		//	GetAnimator()->GetCurAnim()->SetMagnify(GetAnimator()->GetCurAnim()->GetMagnify() - (fDT * 10));
		//}
	}
	else if (m_bClearAnimTimer > 1.f)
	{
		SetPos(Vec2(0.f, 0.f));
		m_bStateClear = true;
		pBody->SetStateClear();
		pHead->SetStateClear();

		m_bGoTrapdoor = false;
		m_bClearAnimTimer = 0.f;
		GetAnimator()->GetCurAnim()->SetFinish();
		GetAnimator()->ResetCurAnim();
		SetScale(Vec2(138.f, 91.f));

		return;
	}

	// 현재 위치랑 트랩도어 위치랑 다르면
	Vec2 vDir = (vPos - GetPos()).Normalize();
	if (vPos != GetPos())
	{
		// 트랩도어 방향으로 이동한다.
		float x = GetPos().x + vDir.x * 500.f * fDT;
		float y = GetPos().y + vDir.y * 500.f * fDT;
		SetPos(Vec2(x, y));
	}
	return;
}

void CPlayer::init()
{
	SetScale(Vec2(138.f, 91.f));


	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 45.f));
	GetCollider()->SetScale(Vec2(40.f, 30.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Hurt", m_pTex, Vec2(0.f, 325.f), Vec2(48.f, 37.f), Vec2(65.f, 0.f), 0.5f, 2, false);
	GetAnimator()->CreateAnimation(L"Jump", m_pTex, Vec2(0.f, 200.f), Vec2(48.f, 37.f), Vec2(65.f, 0.f), 1.f, 2, false);
	GetAnimator()->CreateAnimation(L"GetItem", m_pTex, Vec2(193.f, 262.f), Vec2(48.f, 37.f), Vec2(65.f, 0.f), 1.5f, 1, false);

	
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
	m_bGoTrapdoor = false;
	m_bStateClear = false;

	CreateObject(pBody, GROUP_TYPE::PLAYER);
	CreateObject(pHead, GROUP_TYPE::PLAYER);

}

void CPlayer::OnCollision(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	// monster
	if (L"Monster" == pOtherObj->GetName() || L"Tear_Monster" == pOtherObj->GetName())
	{
		CMonster* pMonster = dynamic_cast<CMonster*>(pOtherObj);

		if (m_finvincibilityTime >= 1.0f)
		{
			m_strAnimName = L"Hurt";
			AnimOper();
			m_finvincibilityTime = 0;

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
		if (m_finvincibilityTime >= 1.0f)
		{
			m_strAnimName = L"Hurt";
			AnimOper();
			m_finvincibilityTime = 0.f;
		}
	}

	if (L"Door" == pOtherObj->GetName())
	{
		CDoor* pdoor = dynamic_cast<CDoor*>(pOtherObj);
		Vec2 vPos = {};

		if (!pdoor->IsOpen())		
		{
			m_pCollobj = pOtherObj;
			m_bcoll = true;
		}
	}

	CObject::OnCollision(_pOther);

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
			case DIR::UP:
				// 문 뒤에있는 방의 위치를 얻어 그 방으로 이동합니다.
				vPos = Vec2(pdoor->GetOwner()->GetRoomPos().x, pdoor->GetOwner()->GetRoomPos().y - 1);
				SetPos(vPos * m_vResolution + (m_vResolution / 2) - Vec2(0.f, -185.f));
				CCamera::GetInst()->SetLookAt(vPos * m_vResolution + (m_vResolution / 2));
				// 들어간 방을 현재 방으로 설정합니다.
				pdoor->GetOwner()->Exit();
				dynamic_cast<CRoom*>(pdoor->GetOwner()->GetOwner()->GetMapData(static_cast<int>(pdoor->GetOwner()->GetRoomPos().y - 1), static_cast<int>(pdoor->GetOwner()->GetRoomPos().x)))->Enter();
				break;
			case DIR::DOWN:
				vPos = Vec2(pdoor->GetOwner()->GetRoomPos().x, pdoor->GetOwner()->GetRoomPos().y + 1);
				SetPos(vPos * m_vResolution + (m_vResolution / 2) - Vec2(0.f, 250.f));
				CCamera::GetInst()->SetLookAt(vPos * m_vResolution + (m_vResolution / 2));
				pdoor->GetOwner()->Exit();
				dynamic_cast<CRoom*>(pdoor->GetOwner()->GetOwner()->GetMapData(static_cast<int>(pdoor->GetOwner()->GetRoomPos().y + 1), static_cast<int>(pdoor->GetOwner()->GetRoomPos().x)))->Enter();
				break;
			case DIR::RIGHT:
				vPos = Vec2(pdoor->GetOwner()->GetRoomPos().x + 1, pdoor->GetOwner()->GetRoomPos().y);
				SetPos(vPos * m_vResolution + (m_vResolution / 2) - Vec2(450.f, 40.f));
				CCamera::GetInst()->SetLookAt(vPos * m_vResolution + (m_vResolution / 2));
				pdoor->GetOwner()->Exit();
				dynamic_cast<CRoom*>(pdoor->GetOwner()->GetOwner()->GetMapData(static_cast<int>(pdoor->GetOwner()->GetRoomPos().y), static_cast<int>(pdoor->GetOwner()->GetRoomPos().x + 1)))->Enter();
				break;
			case DIR::LEFT:
				vPos = Vec2(pdoor->GetOwner()->GetRoomPos().x - 1, pdoor->GetOwner()->GetRoomPos().y);
				SetPos(vPos * m_vResolution + (m_vResolution / 2) - Vec2(-450.f, 40.f));
				CCamera::GetInst()->SetLookAt(vPos * m_vResolution + (m_vResolution / 2));
				pdoor->GetOwner()->Exit();
				dynamic_cast<CRoom*>(pdoor->GetOwner()->GetOwner()->GetMapData(static_cast<int>(pdoor->GetOwner()->GetRoomPos().y), static_cast<int>(pdoor->GetOwner()->GetRoomPos().x - 1)))->Enter();
				break;
			default:
				break;
			}
		}
	}

	// wall
	if (L"Wall" == pOtherObj->GetName())
	{
		CWallCollider* pWall = dynamic_cast<CWallCollider*>(pOtherObj);

		switch (pWall->GetDir())
		{
		case DIR::UP:
			m_arrWallDirCheck[static_cast<UINT>(DIR::UP)] = true;
			break;
		case DIR::DOWN:
			m_arrWallDirCheck[static_cast<UINT>(DIR::DOWN)] = true;
			break;
		case DIR::RIGHT:
			m_arrWallDirCheck[static_cast<UINT>(DIR::RIGHT)] = true;
			break;
		case DIR::LEFT:
			m_arrWallDirCheck[static_cast<UINT>(DIR::LEFT)] = true;	
			break;		
		default:
			break;
		}
		this->GetRigidBody()->SetVelocity(Vec2(0, 0));
	}
	
	// item
	if (L"Item" == pOtherObj->GetName())
	{
		CItem* pItem = dynamic_cast<CItem*>(pOtherObj);
		++(m_vInventory[static_cast<UINT>(pItem->GetItemName())]);
		m_GetItemCheck = pItem;

		// 보유 아이템 체크 얻은 아이템이 있으면 itemcheck에서 획득처리
		if (nullptr != m_GetItemCheck)
		{
			ItemCheck();

			m_GetItemCheck = nullptr;
		}

		
		m_strAnimName = L"GetItem";
		if (GetAnimator()->GetCurAnim() != GetAnimator()->FindAnimation(L"GetItem"))
		{
			AnimOper();
		}

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

		m_strAnimName = L"Hurt";
		if (GetAnimator()->GetCurAnim() != GetAnimator()->FindAnimation(L"Hurt"))
		{
			AnimOper();
			m_finvincibilityTime = 0;
		}

	}

	if (L"Monster" == pOtherObj->GetName() || L"Tear_Monster" == pOtherObj->GetName())
	{

		Vec2 vDir = pOtherObj->GetPos() - GetPos();
		vDir.Normalize();
		vDir = vDir * 500.f;
		Vec2 vResult = GetRigidBody()->GetVelocity() - vDir;
		GetRigidBody()->SetVelocity(vResult);

		m_strAnimName = L"Hurt";
		if(GetAnimator()->GetCurAnim() != GetAnimator()->FindAnimation(L"Hurt"))
		{
			AnimOper();

			m_finvincibilityTime = 0;
			m_iPrevHp = m_pStat->m_iHP;
			--m_pStat->m_iHP;

		}
	}

	if (!m_bGoTrapdoor)
	{
		if (L"Trapdoor" == pOtherObj->GetName())
		{
			m_bGoTrapdoor = true;
			m_strAnimName = L"Jump";
			if (GetAnimator()->GetCurAnim() != GetAnimator()->FindAnimation(L"Jump"))
			{
				AnimOper();
			}
		}

	}

	CObject::OnCollisionEnter(_pOther);


}

void CPlayer::OnCollisionExit(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	// wall
	if (L"Wall" == pOtherObj->GetName())
	{
		CWallCollider* pWall = dynamic_cast<CWallCollider*>(pOtherObj);

		switch (pWall->GetDir())
		{
		case DIR::UP:
			m_arrWallDirCheck[static_cast<UINT>(DIR::UP)] = false;
			break;
		case DIR::DOWN:
			m_arrWallDirCheck[static_cast<UINT>(DIR::DOWN)] = false;
			break;
		case DIR::RIGHT:
			m_arrWallDirCheck[static_cast<UINT>(DIR::RIGHT)] = false;
			break;
		case DIR::LEFT:
			m_arrWallDirCheck[static_cast<UINT>(DIR::LEFT)] = false;
			break;

		default:
			break;
		}
	}

}

void CPlayer::CreateMissile(Vec2 _vDir)
{


}

void CPlayer::ItemCheck()
{
	m_pItemTex = m_GetItemCheck->GetItemTex();

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
	if (ITEM_TABLE::thewafer == m_GetItemCheck->GetItemName())
	{
		m_bIsWafer = true;
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

