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
	void CreateParticle(PARTICLE_TYPE _eType, Vec2 _vPos); // 직접 추가용
//	void CreateParticle(PARTICLE_TYPE _eType); // 오브젝트 풀링

	
private: 
	vector<CParticle*>	m_arrParticlePool[(UINT)PARTICLE_TYPE::END];



};

