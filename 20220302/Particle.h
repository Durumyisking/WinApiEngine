#pragma once
#include "Object.h"
#include "ParticleMgr.h"

class CParticle :
    public CObject
{
protected:
    CTexture* m_pTex;

public:
    CParticle(Vec2 _vPos);
    ~CParticle();

    CLONE(CParticle);


public:
    virtual void update();
    virtual void render(HDC _dc);


};

