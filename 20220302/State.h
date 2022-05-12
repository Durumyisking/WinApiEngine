#pragma once

class CAI;

class CState
{
private:
	// 부모AI
	CAI*		m_pAI;
	// 상태
	MON_STATE	m_eState;


public:
	CState(MON_STATE _eState);
	// 상속시켜 파생시킬 함수라서 소멸자에 가상함수
	virtual ~CState();

public:
	// AI 상태 진입 탈출 처리
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	// 로직 처리
	virtual void update() = 0;

public:
	CAI* GetAI() {	return m_pAI;}

	void SetState(MON_STATE& _strKey) { m_eState = _strKey; }
	MON_STATE GetType() const { return m_eState; }


	friend class CAI;
};

