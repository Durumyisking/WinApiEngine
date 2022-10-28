#include "pch.h"
#include "Object.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
#include "Camera.h"

#include "Collider.h"
#include "Animator.h"
#include "Animation.h"

#include "RigidBody.h"

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


void CObject::finalupdate()
{

	if (m_pCollider)
		m_pCollider->finalupdate();

	if (m_pAnimator)
		m_pAnimator->finalupdate();

	if (m_pRigidBody)
		m_pRigidBody->finalupdate();
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


