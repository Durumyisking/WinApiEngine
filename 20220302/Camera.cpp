#include "pch.h"
#include "Camera.h"

#include "Object.h"
#include "Core.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
#include "ResMgr.h"
#include "Texture.h"	


CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(0.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.5f)
	, m_pVeilTex(nullptr)
{
}


CCamera::~CCamera()
{
}



void CCamera::init()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);

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

void CCamera::render(HDC _dc)
{
	// 카메라 이펙트가 있는지 확인
	if(m_listCamEffect.empty())
		return;

	// 시간 누적값 체크
	tCamEffect& effect =  m_listCamEffect.front();
	effect.m_fCurTime += fDT;

	float fRatio = 0.f; // 이팩트 진행 비율
	fRatio = effect.m_fCurTime / effect.m_fDuration;

	if (fRatio < 0.f)
		fRatio = 0.f;
	if (fRatio > 1.f)
		fRatio = 1.f;

	int iAlpha = 0;

	if (CAM_EFFECT::FADE_OUT == effect.eEffect)
	{
		iAlpha = static_cast<int>(255.f* fRatio);
	}

	else if (CAM_EFFECT::FADE_IN == effect.eEffect)
	{
		iAlpha = static_cast<int>(255.f* (1.f - fRatio));
	}

	

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;

	AlphaBlend(_dc
		, 0	, 0
		, static_cast<int>(m_pVeilTex->GetWidth())
		, static_cast<int>(m_pVeilTex->GetHeight())
		, m_pVeilTex->GetDC()
		, 0	, 0
		, static_cast<int>(m_pVeilTex->GetWidth())
		, static_cast<int>(m_pVeilTex->GetHeight())
		, bf
	);

	// 진행시간이 이펙트 최대 지정 넘어가면
	if (effect.m_fDuration < effect.m_fCurTime)
	{
		m_listCamEffect.pop_front();
		return;
	}

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

		if (vLookDir.IsZero())
		{
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize()*m_fSpeed * fDT;
		}
	}

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;

}
