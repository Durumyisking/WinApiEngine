#include "pch.h"
#include "Camera.h"

#include "Object.h"
#include "Core.h"

#include "TimeMgr.h"
#include "KeyMgr.h"


CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(0.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.5f)
{
}


CCamera::~CCamera()
{
}



void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 300.f * fDT;
	if (KEY_HOLD(KEY::DOWN))
		m_vLookAt.y += 300.f * fDT;
	if (KEY_HOLD(KEY::LEFT))
		m_vLookAt.x -= 300.f * fDT;
	if (KEY_HOLD(KEY::RIGHT))
		m_vLookAt.x += 300.f * fDT;

	// 화면 중앙좌표와 카메라 LookAt 좌표값과의 차이
	// 그 차이만큼 다른 OBj들을 반대로 이동시켜줄것
	CalDiff();

}

void CCamera::CalDiff()
{
	// prevlook 과 현재look의 차이값을 보정해서 현재의 lookat을 구한다.
	// m_vLookAt - m_vPrevLookAt = 방향

	m_fAccTime += fDT;

	if (m_fTime <= m_fAccTime)
	{
		// 지정한 시간이 되지 않았을때에는 계산해둔 속도에 맞춰서 이동
		// SetLookat과 같이 움직임
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;
		m_vCurLookAt = m_vPrevLookAt + vLookDir.Nomalize()*m_fSpeed * fDT;
	}

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;

}
