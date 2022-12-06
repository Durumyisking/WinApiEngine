#pragma once

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
	void CreateParticle(PARTICLE_TYPE _eType, Vec2 _vPos);




};

