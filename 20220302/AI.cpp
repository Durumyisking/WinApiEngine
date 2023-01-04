#include "pch.h"
#include "AI.h"

#include "State.h"

CMonsterAI::CMonsterAI()
	: m_pCurState(nullptr)
	, m_pOwner(nullptr)
{
}

CMonsterAI::~CMonsterAI()
{
	// �����ɶ� map�� �Ҵ��� state ����
	Safe_Delete_Map(m_pmapState);
}


void CMonsterAI::update()
{
	m_pCurState->update();
}

void CMonsterAI::AddState(CState * _pState)
{
	CState* pState = GetState(_pState->GetType());
	// pState�� ������ ����
	assert(!pState);

	m_pmapState.insert(make_pair(_pState->GetType(), _pState));
	_pState->m_pAI = this;
}

CState * CMonsterAI::GetState(MON_STATE _eState)
{
	map<MON_STATE, CState*>::iterator iter = m_pmapState.find(_eState);

	if (iter == m_pmapState.end())
		return nullptr;


	return iter->second;
}

void CMonsterAI::ChangeState(MON_STATE _eNextState)
{
	CState* pNextState = GetState(_eNextState);
	
	assert(m_pCurState != pNextState);

	m_pCurState->Exit();
	m_pCurState = pNextState;
	m_pCurState->Enter();

}
