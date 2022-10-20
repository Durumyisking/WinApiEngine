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
	, m_pCollider{}
	, m_pAnimator(nullptr)
	, m_bAlive(true)
	, m_vResolution(CCore::GetInst()->GetResolution())

{
}

CObject::CObject(const CObject& _origin)
	: m_strName(_origin.m_strName)
	, m_vPos{_origin.m_vPos}
	, m_vScale{_origin.m_vScale}
	, m_pCollider{}
	, m_pAnimator(nullptr)
	, m_bAlive(true)
{
	if (!(_origin.m_pCollider.empty()))
	{
		for (size_t i = 0; i < _origin.m_pCollider.size(); i++)
		{
			m_pCollider[i] = new CCollider(_origin.m_pCollider[i]);
		}
	}
	if (_origin.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator);
		//m_pAnimator->m_pOwner = this;
	}
}

CObject::~CObject()
{
	if (!m_pCollider.empty())
	for (size_t i = 0; i < m_pCollider.size(); i++)
	{
		delete m_pCollider[i];
	}	

	if (nullptr != m_pAnimator)
		delete m_pAnimator;

	if (nullptr != m_pRigidBody)
		delete m_pRigidBody;
}


void CObject::CreateCollider(wstring _strColliderName)
{
	CCollider* pTemp = new CCollider;
	pTemp->m_pOwner = this;
	pTemp->SetName(_strColliderName);
	m_pCollider.push_back(pTemp);
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

//void CObject::PlayAnim(CAnimation * _pAnim, const wstring & _AnimName, Vec2 _vOffset,  bool _Repeat, float	_fMagnify)
//{
//	GetAnimator()->Play(_AnimName, _Repeat);
//
//	_pAnim = GetAnimator()->FindAnimation(_AnimName);
//
//	for (UINT i = 0; i < (UINT)_pAnim->GetMaxFrame(); ++i)
//		_pAnim->GetFrame(i).vOffset = Vec2(_vOffset);
//
//}

void CObject::PlayAnim(CAnimation * _pAnim, const wstring & _AnimName, Vec2 _vOffset, bool _Repeat)
{
	GetAnimator()->Play(_AnimName, _Repeat);

	_pAnim = GetAnimator()->FindAnimation(_AnimName);

	for (UINT i = 0; i < (UINT)_pAnim->GetMaxFrame(); ++i)
		_pAnim->GetFrame(i).vOffset = Vec2(_vOffset);
}


void CObject::finalupdate()
{

	if (!m_pCollider.empty())
	for (size_t i = 0; i < m_pCollider.size(); i++)
	{
		m_pCollider[i]->finalupdate();
	}

	if (m_pAnimator)
		m_pAnimator->finalupdate();

	if (m_pRigidBody)
		m_pRigidBody->finalupdate();
}

void CObject::render(HDC _dc)
{
	// ��¥ ��ǥ�� �ƴ� ������ �Ǵ� ��ǥ (��¥ ��ǥ�� m_vPos)
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);

	component_render(_dc);
}

void CObject::component_render(HDC _dc)
{

	if (nullptr != m_pAnimator)
	{
		m_pAnimator->render(_dc);
	}


	// Collider�� ���߿� rendering�ǰ�
	if (!m_pCollider.empty())
	for (size_t i = 0; i < m_pCollider.size(); i++)
	{
		m_pCollider[i]->render(_dc);
		// ���θ� �������� ä��� hollow brush ���
	}
	
}


