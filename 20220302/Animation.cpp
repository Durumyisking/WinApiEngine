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
	, m_fMagnify(3.f)
	, m_vOffset()
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

		// ex ) ������ ABCDE����
		// A�� �� �ɷȴٰ� ���������� ���� 3�ʵ��� ���ɸ��� C�� ���־�� �ϴµ�
		// �ٸ����� �� �������� ����
		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;

	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;

	HDC Reversdc, Outputdc;
	Reversdc = CreateCompatibleDC(_dc);

	Outputdc = m_pTex->GetDC();


	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	Vec2 vScale = pObj->GetScale();

	int iWidth = (int)m_pTex->GetWidth();
	int iHeight = (int)m_pTex->GetHeight();


	// �츮�� �ִϸ��̼��� ���ʿ� �ݶ��̴��� �Ѱű� ������ offset���� �ִϸ��̼� ���� �ø���
	// ��¥��ġ
	vPos = vPos + m_vecFrm[m_iCurFrm].vOffset;

	// ������ ��ġ
	vPos = CCamera::GetInst()->GetRenderPos(vPos);



	//BLENDFUNCTION bf = {};

	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.AlphaFormat = AC_SRC_ALPHA;
	//// ���� ���İ� ( �̰� �ٲ㼭 ���� ���� )
	//bf.SourceConstantAlpha = 255;

	//AlphaBlend(_dc
	//	, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f) - vScale.x / 3.f
	//	, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f) - vScale.y / 3.f
	//	, (int)(m_vecFrm[m_iCurFrm].vSlice.x) * 3
	//	, (int)(m_vecFrm[m_iCurFrm].vSlice.y) * 3
	//	, Outputdc
	//	, (int)(m_vecFrm[m_iCurFrm].vLT.x)
	//	, (int)(m_vecFrm[m_iCurFrm].vLT.y)
	//	, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
	//	, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
	//	, bf
	//);




	TransparentBlt(_dc
		, static_cast<int>(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f - (vScale.x / m_fMagnify) + m_vOffset.x)
		, static_cast<int>(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f - (vScale.y / m_fMagnify) + m_vOffset.y)
		, static_cast<int>(m_vecFrm[m_iCurFrm].vSlice.x * m_fMagnify)
		, static_cast<int>(m_vecFrm[m_iCurFrm].vSlice.y * m_fMagnify)
		, Outputdc
		, static_cast<int>(m_vecFrm[m_iCurFrm].vLT.x)
		, static_cast<int>(m_vecFrm[m_iCurFrm].vLT.y)
		, static_cast<int>(m_vecFrm[m_iCurFrm].vSlice.x)
		, static_cast<int>(m_vecFrm[m_iCurFrm].vSlice.y)
		, RGB(255, 0, 255)
	);

	DeleteObject(Reversdc);
}

void CAnimation::Create(CTexture * _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};
	// iframecount ������ŭ ������ ���� ����
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * (float)i;

		m_vecFrm.push_back(frm);

	}
}
