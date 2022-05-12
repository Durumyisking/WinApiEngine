#include "pch.h"
#include "AI.h"

#include "State.h"

CAI::CAI()
	: m_pCurState(nullptr)
	, m_pOwner(nullptr)
{
}

CAI::~CAI()
{
	// �����ɶ� map�� �Ҵ��� state ����
	Safe_Delete_Map(m_pmapState);
}


void CAI::update()
{


	m_pCurState->update();
}

void CAI::AddState(CState * _pState)
{
	CState* pState = GetState(_pState->GetType());
	// pState�� ������ ����
	assert(!pState);

	m_pmapState.insert(make_pair(_pState->GetType(), _pState));
	_pState->m_pAI = this;
}

CState * CAI::GetState(MON_STATE _eState)
{
	map<MON_STATE, CState*>::iterator iter = m_pmapState.find(_eState);

	if (iter == m_pmapState.end())
		return nullptr;


	return iter->second;
}
