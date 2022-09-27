#pragma once

class CState;
class CMonster;

//  AI클래스는
// 몬스터가 가진 여러가지 AI state 들 중에서 전환할 수 있게 해주는 클래스
// 여기에다가 행동패턴을 구현하지는 않을것
class CAI
{
private:
	// 해당 AI를 가질 몬스터를 설정
	CMonster*				m_pOwner;
	// monster의 state 구조체
	map<MON_STATE, CState*>	m_pmapState;
	CState*					m_pCurState;

public:
	CAI();
	~CAI();

public:
	void update();

public:
	void AddState(CState* _pState);
	CState* GetState(MON_STATE _eState);
	CMonster* GetOwner() const { return m_pOwner; }

	void SetCurState(MON_STATE _eState) { m_pCurState = m_pmapState.find(_eState)->second; }
	void ChangeState(MON_STATE _eNextState);


	friend class CMonster;
};

