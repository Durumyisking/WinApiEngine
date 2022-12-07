#pragma once

class CParticle;


enum class PARTICLE_TYPE
{
	blood,
	bomb,

	END
};

class CParticleMgr
{
	SINGLE(CParticleMgr);

public:
	void init();
	void CreateParticle(PARTICLE_TYPE _eType, Vec2 _vPos); // ���� �߰���
//	void CreateParticle(PARTICLE_TYPE _eType); // ������Ʈ Ǯ��

	
private: 
	vector<CParticle*>	m_arrParticlePool[(UINT)PARTICLE_TYPE::END];



};

