#include "pch.h"
#include "Object.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
#include "Camera.h"

#include "Collider.h"
#include "Animator.h"
#include "Animation.h"

#include "RigidBody.h"
#include "Door.h"
#include "Core.h"

CObject::CObject()
	: m_vPos{}
	, m_vPosTemp{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bAlive(true)
	, m_vResolution(CCore::GetInst()->GetResolution())
	, m_pOwner(nullptr)
	, m_MoveFlag(0x00)
	, m_pRigidBody(nullptr)
	, m_pCollobj(nullptr)
	, m_bcoll(false)
	, m_LastMoveFlag(0)

{
}

CObject::CObject(CRoom* _pOwner)
	: m_vPos{}
	, m_vPosTemp{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bAlive(true)
	, m_vResolution(CCore::GetInst()->GetResolution())
	, m_pOwner(_pOwner)
	, m_MoveFlag(0x00)
	, m_pRigidBody(nullptr)
	, m_pCollobj(nullptr)
	, m_bcoll(false)
	, m_LastMoveFlag(0)
{
}

CObject::CObject(const CObject& _origin)
	: m_strName(_origin.m_strName)
	, m_vPos{_origin.m_vPos}
	, m_vScale{_origin.m_vScale}
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)

	, m_bAlive(true)
	, m_pOwner(nullptr)
	, m_MoveFlag(_origin.m_MoveFlag)
	, m_pRigidBody(nullptr)
	, m_pCollobj(nullptr)
	, m_bcoll(false)
	, m_LastMoveFlag(0)
{
	if (_origin.m_pCollider)
	{
		m_pCollider = new CCollider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this;
	}
	if (_origin.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator);
		//m_pAnimator->m_pOwner = this;
	}
}

CObject::~CObject()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;

	if (nullptr != m_pAnimator)
		delete m_pAnimator;

	if (nullptr != m_pRigidBody)
		delete m_pRigidBody;
}


void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}

void CObject::CreateRigidBody()
{
	m_pRigidBody = new CRigidBody;
	m_pRigidBody->m_pOwner = this;
}



void CObject::PlayAnim(CAnimation * _pAnim, const wstring & _AnimName, Vec2 _vOffset, bool _Repeat)
{

	GetAnimator()->Play(_AnimName, _Repeat);

	_pAnim = GetAnimator()->FindAnimation(_AnimName);

	for (UINT i = 0; i < (UINT)_pAnim->GetMaxFrame(); ++i)
		_pAnim->GetFrame(i).vOffset = Vec2(_vOffset);
}

void CObject::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (L"Fire" == pOtherObj->GetName() || L"Poop" == pOtherObj->GetName() || L"Monster" == pOtherObj->GetName() || L"Player" == pOtherObj->GetName() || L"Door" == pOtherObj->GetName())
	{
		Vec2 vTemp = IntersectArea(pOtherObj);
		SetPos(GetPos() - vTemp);
	}
}

void CObject::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (L"Fire" == pOtherObj->GetName() || L"Poop" == pOtherObj->GetName() || L"Monster" == pOtherObj->GetName() || L"Player" == pOtherObj->GetName() || L"Door" == pOtherObj->GetName())
	{
		if (L"Door" == pOtherObj->GetName())
		{
			CDoor* pdoor = dynamic_cast<CDoor*>(pOtherObj);
			if (pdoor->IsOpen())
				return;
		}

		Vec2 vTemp = IntersectArea(pOtherObj);
		SetPos(GetPos() - vTemp);
	}
}

void CObject::OnCollisionExit(CCollider* _pOther)
{
	m_LastMoveFlag = 0;

}


Vec2 CObject::IntersectArea(CObject* _pOther)
{
	if (nullptr == _pOther->GetCollider())
		return Vec2(0.f, 0.f);

	Vec2 MyScale = GetCollider()->GetScale();
	Vec2 MyPos = GetCollider()->GetFinalPos();
	RECT MyRect{};
	MyRect.left = static_cast<int>(MyPos.x - (MyScale.x / 2.f));
	MyRect.right = static_cast<int>(MyPos.x + (MyScale.x / 2.f));
	MyRect.top = static_cast<int>(MyPos.y - (MyScale.y / 2.f));
	MyRect.bottom = static_cast<int>(MyPos.y + (MyScale.y / 2.f));

	Vec2 OtherScale = _pOther->GetCollider()->GetScale();
	Vec2 OtherPos = _pOther->GetCollider()->GetFinalPos();
	RECT OtherRect{};
	OtherRect.left = static_cast<int>(OtherPos.x - (OtherScale.x / 2.f));
	OtherRect.right = static_cast<int>(OtherPos.x + (OtherScale.x / 2.f));
	OtherRect.top = static_cast<int>(OtherPos.y - (OtherScale.y / 2.f));
	OtherRect.bottom = static_cast<int>(OtherPos.y + (OtherScale.y / 2.f));


	RECT Result{};
	IntersectRect(&Result, &MyRect, &OtherRect);

	int x = Result.right - Result.left;
	int y = Result.bottom - Result.top;

	Vec2 vecResult { x, y };
	Vec2 vOffset {1.f, 1.f};
	Vec2 vDir = {};


	switch (static_cast<int>(m_LastMoveFlag))
	{
	case static_cast<int>(MOVE_FLAG::UP):
		vDir = { 0.f , -1.f };
		break;
	case static_cast<int>(MOVE_FLAG::DOWN):
		vDir = { 0.f , 1.f };
		break;
	case static_cast<int>(MOVE_FLAG::LEFT):
		vDir = { -1.f , 0.f };
		break;
	case static_cast<int>(MOVE_FLAG::RIGHT):
		vDir = { 1.f , 0.f };
		break;

	case (static_cast<int>(MOVE_FLAG::DOWN) + static_cast<int>(MOVE_FLAG::LEFT)):
		if (x > y)	
			vDir = { 0.f , 1.f };
		else //if (x < y)
			vDir = { -1.f , 0.f };
		break;
	case (static_cast<int>(MOVE_FLAG::DOWN) + static_cast<int>(MOVE_FLAG::RIGHT)):
		if (x > y)
			vDir = { 0.f , 1.f };
		else //if (x < y)
			vDir = { 1.f , 0.f };
		break;
	case (static_cast<int>(MOVE_FLAG::UP) + static_cast<int>(MOVE_FLAG::RIGHT)):
		if (x > y)
			vDir = { 0.f , -1.f };
		else //if (x < y)
			vDir = { 1.f , 0.f };
		break;
	case (static_cast<int>(MOVE_FLAG::UP) + static_cast<int>(MOVE_FLAG::LEFT)):
		if (x > y)
			vDir = { 0.f , -1.f };
		else //if(x < y)
			vDir = { -1.f , 0.f };
		break;

	}
	vecResult += vOffset;
	vecResult = vecResult * vDir;

	//if(vDir.IsZero())
	//	m_LastMoveFlag = 0;

	//GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
	//GetRigidBody()->SetForce(Vec2(0.f, 0.f));


	return vecResult;
}

void CObject::finalupdate()
{
	if (m_pRigidBody)
		m_pRigidBody->finalupdate();

	if (m_pCollider)
		m_pCollider->finalupdate();

	if (m_pAnimator)
		m_pAnimator->finalupdate();
}

void CObject::render(HDC _dc)
{
	// 진짜 좌표가 아닌 렌더링 되는 좌표 (진짜 좌표는 m_vPos)
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);

	component_render(_dc);
}

void CObject::component_render(HDC _dc)
{

	if (nullptr != m_pAnimator)
	{		
		m_pAnimator->render(_dc);
	}


	// Collider가 나중에 rendering되게
	if (nullptr != m_pCollider)
	{
		m_pCollider->render(_dc);
		// 내부를 공백으로 채우는 hollow brush 사용
	}
}


