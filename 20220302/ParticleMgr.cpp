#include "pch.h"
#include "ParticleMgr.h"
#include "Particle.h"

CParticleMgr::CParticleMgr()
	: m_arrParticlePool()
{

}
CParticleMgr::~CParticleMgr()
{

}

void CParticleMgr::init()
{
	for (UINT i = 0; i < static_cast<UINT>(PARTICLE_TYPE::END); i++)
	{	
		for (int j = 0; j < 100; j++)
		{
			CParticle* pNewParticle = new CParticle(static_cast<PARTICLE_TYPE>(i));
			m_arrParticlePool[i].push_back(pNewParticle);
		}
	}

}

void CParticleMgr::CreateParticle(PARTICLE_TYPE _eType, Vec2 _vPos)
{
	if (!m_arrParticlePool[static_cast<UINT>(_eType)].empty())
	{
		// ���� Ÿ�Կ� �´� ������ ������ �ε����� �ִ°� �̾ƿ�
		CParticle* pNewParticle = m_arrParticlePool[static_cast<UINT>(_eType)][m_arrParticlePool[static_cast<UINT>(_eType)].size() - 1];
		pNewParticle->SetPos(_vPos);
		// �̾ƿ����� popback;
		m_arrParticlePool[static_cast<UINT>(_eType)].pop_back();

		CreateObject(pNewParticle, GROUP_TYPE::PARTICLE);
	}
	else
	{
		CParticle* pNewParticle = new CParticle(_vPos, _eType);
		CreateObject(pNewParticle, GROUP_TYPE::PARTICLE);
	}
}

//void CParticleMgr::CreateParticle(PARTICLE_TYPE _eType)
//{
//	CParticle* pNewParticle = new CParticle(_eType);
//
//
//	CreateObject(pNewParticle, GROUP_TYPE::PARTICLE);
//
//}
