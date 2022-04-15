#include "pch.h"
#include "Animation.h"
#include "Animator.h"

#include "Texture.h"
#include "Object.h"

#include "TimeMgr.h"
#include "Camera.h"


CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}


CAnimation::~CAnimation()
{
}

void CAnimation::update()
{
	if (m_bFinish)
		return;

	m_fAccTime += fDT;

	if (m_fAccTime > m_vecFrm[m_iCurFrm].fDuration)
	{
		++m_iCurFrm;

		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			return;
		}

		// ex ) 프레임 ABCDE에서
		// A서 렉 걸렸다고 생각했을때 원래 3초동안 랙걸리면 C로 가있어야 하는데
		// 다른곳에 가 있을수도 있음
		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;

	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;

	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	Vec2 vScale = pObj->GetScale();

	// 우리는 애니메이션의 발쪽에 콜라이더를 둘거기 때문에 offset으로 애니메이션 위로 올릴거
	// 진짜위치
	vPos = vPos + m_vecFrm[m_iCurFrm].vOffset;

	// 렌더링 위치
//	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f) - vScale.x / 3.f
		, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f) - vScale.y / 3.f
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x) * 3
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y) * 3
		, m_pTex->GetDC()
		, (int)(m_vecFrm[m_iCurFrm].vLT.x)
		, (int)(m_vecFrm[m_iCurFrm].vLT.y)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
		, RGB(255, 0, 255)
	);
}

void CAnimation::Create(CTexture * _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};
	// iframecount 개수만큼 프레임 정보 만듦
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * (float)i;

		m_vecFrm.push_back(frm);

	}
}
