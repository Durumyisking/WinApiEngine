#pragma once

class CObject;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct tCamEffect
{
	CAM_EFFECT	eEffect;		// 카메라 효과
	float		m_fDuration;	// 효과 진행 시간
	float		m_fCurTime;		// 카메라 효과 현재 진행된 시간
};


class CCamera
{
	SINGLE(CCamera);

private:
	Vec2				m_vLookAt;		// 카메라가 보고 있는곳 (화면의 중심)
	Vec2				m_vPrevLookAt;	// 카메라가 보는 이전프레임 위치
										// 이 두 위치의 차이가 급격하게 벌어지면 스무스하게 이동하는게 보기 좋음!
	Vec2				m_vCurLookAt;	// 이전 위치와 현재 위치 보정위치 (찐 Lookat) // 현재 화면의 중앙

	CObject*			m_pTargetObj;	// 카메라 타겟 오브젝트

	Vec2				m_vDiff;		// 해상도 중심위치와, 카메라 LookAt간의 차이값

	float				m_fTime;		// 타겟을 따라가는데 걸리는 시간
	float				m_fSpeed;		// 타겟 추적속도
	float				m_fAccTime;		// 누적시간

	CTexture*			m_pVeilTex;			// 카메라 가림막 텍스처(검은색으로)
	list <tCamEffect>	m_listCamEffect;

public:
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 GetLookAt() { return m_vCurLookAt; }
	void SetLookAt(Vec2 _vLook)
	{
		// 거리 = 속력 * 시간
		m_vLookAt = _vLook;
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}

	void SetLookAtDirect(Vec2 _vLook)
	{
		m_vLookAt = _vLook;
	}

	Vec2 GetRenderPos(Vec2 _vObjPos){ return _vObjPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) {return  _vRenderPos + m_vDiff; }

	void FadeIn(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_IN;
		ef.m_fDuration = _fDuration;
		ef.m_fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		if (0.f == _fDuration)
			assert(nullptr);
	}

	void FadeOut(float _fDuration) 
	{ 
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_OUT;
		ef.m_fDuration = _fDuration;
		ef.m_fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		if (0.f == _fDuration)
			assert(nullptr);
	}
	
public:
	void init();
	void update();
	void render(HDC _dc);

private:
	// 윈도우 화면 중앙에서부터 얼마나 떨어져 있는지
	void CalDiff();
};

