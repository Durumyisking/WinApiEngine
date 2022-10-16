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

	if (KEY_HOLD(KEY::I))
		m_vLookAt.y -= 1000.f * fDT;
	if (KEY_HOLD(KEY::K))
		m_vLookAt.y += 1000.f * fDT;
	if (KEY_HOLD(KEY::J))
		m_vLookAt.x -= 1000.f * fDT;
	if (KEY_HOLD(KEY::L))
		m_vLookAt.x += 1000.f * fDT;

	// ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ������ ����
	// �� ���̸�ŭ �ٸ� OBj���� �ݴ�� �̵������ٰ�
	CalDiff();

}

void CCamera::render(HDC _dc)
{
	// ī�޶� ����Ʈ�� �ִ��� Ȯ��
	if(m_listCamEffect.empty())
		return;

	// �ð� ������ üũ
	tCamEffect& effect =  m_listCamEffect.front();
	effect.m_fCurTime += fDT;

	float fRatio = 0.f; // ����Ʈ ���� ����
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

	// ����ð��� ����Ʈ �ִ� ���� �Ѿ��
	if (effect.m_fDuration < effect.m_fCurTime)
	{
		m_listCamEffect.pop_front();
		return;
	}

}

void CCamera::CalDiff()
{
	// prevlook �� ����look�� ���̰��� �����ؼ� ������ lookat�� ���Ѵ�.
	// m_vLookAt - m_vPrevLookAt = ����

	m_fAccTime += fDT;

	if (m_fTime <= m_fAccTime)
	{
		// ������ �ð��� ���� �ʾ��������� ����ص� �ӵ��� ���缭 �̵�
		// SetLookat�� ���� ������
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;		
		m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize()*m_fSpeed * fDT;
		
	}

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;

}
