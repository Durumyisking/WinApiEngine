#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera);

private:
	Vec2		m_vLookAt;		// 카메라가 보고 있는곳 (화면의 중심)
	Vec2		m_vPrevLookAt;	// 카메라가 보는 이전프레임 위치
	// 이 두 위치의 차이가 급격하게 벌어지면 스무스하게 이동하는게 보기 좋음!
	Vec2		m_vCurLookAt;	// 이전 위치와 현재 위치 보정위치 (찐 Lookat)

	CObject*	m_pTargetObj;	// 카메라 타겟 오브젝트

	Vec2		m_vDiff;		// 해상도 중심위치와, 카메라 LookAt간의 차이값

	float		m_fTime;			// 타겟을 따라가는데 걸리는 시간
	float		m_fSpeed;
	float		m_fAccTime;


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
	Vec2 GetRenderPos(Vec2 _vObjPos){ return _vObjPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) {return  _vRenderPos + m_vDiff; }

public:
	void update();

private:
	// 윈도우 화면 중앙에서부터 얼마나 떨어져 있는지
	void CalDiff();
};

