#pragma once

class CState;
class CMonster;

//  AIŬ������
// ���Ͱ� ���� �������� AI state �� �߿��� ��ȯ�� �� �ְ� ���ִ� Ŭ����
// ���⿡�ٰ� �ൿ������ ���������� ������
class CAI
{
private:
	// �ش� AI�� ���� ���͸� ����
	CMonster*				m_pOwner;
	// monster�� state ����ü
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

	void SetCurState(MON_STATE _eState) { m_pCurState = m_pmapState.find(_eState)->second; }


	friend class CMonster;
};
