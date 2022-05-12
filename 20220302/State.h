#pragma once

class CAI;

class CState
{
private:
	// �θ�AI
	CAI*		m_pAI;
	// ����
	MON_STATE	m_eState;


public:
	CState(MON_STATE _eState);
	// ��ӽ��� �Ļ���ų �Լ��� �Ҹ��ڿ� �����Լ�
	virtual ~CState();

public:
	// AI ���� ���� Ż�� ó��
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	// ���� ó��
	virtual void update() = 0;

public:
	CAI* GetAI() {	return m_pAI;}

	void SetState(MON_STATE& _strKey) { m_eState = _strKey; }
	MON_STATE GetType() const { return m_eState; }


	friend class CAI;
};

