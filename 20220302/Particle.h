#pragma once
#include "Object.h"
#include "ParticleMgr.h"

class CParticle :
    public CObject
{
protected:
    CTexture* m_pTex;

public:
    CParticle(Vec2 _vPos, PARTICLE_TYPE _eType);
    CParticle(PARTICLE_TYPE _eType);
    ~CParticle();

    CLONE(CParticle);


public:
    virtual void update();
    virtual void render(HDC _dc);


public:
    PARTICLE_TYPE   m_eType;
    Vec2            m_vSliceQuant;
    Vec2            m_vSlice;
    Vec2            m_vSliceGap;


};

