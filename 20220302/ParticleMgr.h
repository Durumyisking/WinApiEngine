#pragma once

class CParticle;


enum class PARTICLE_TYPE
{
	bloodpool,
	bloodstain,
	bloodgibs,
	bombradius,

	END
};

class CParticleMgr
{
	SINGLE(CParticleMgr);

public:
	void init();
	void CreateParticle(PARTICLE_TYPE _eType, Vec2 _vPos, Vec2 _vDir); // ���� �߰���
//	void CreateParticle(PARTICLE_TYPE _eType); // ������Ʈ Ǯ��

	
private: 
	vector<CParticle*>	m_arrParticlePool[(UINT)PARTICLE_TYPE::END];



};

