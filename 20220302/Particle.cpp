#include "pch.h"
#include "Particle.h"

#include "RigidBody.h"
#include "Texture.h"
#include "ResMgr.h"


CParticle::CParticle(Vec2 _vPos, PARTICLE_TYPE _eType)
	: m_pTex(nullptr)
	, m_eType(_eType)
	, m_vSliceQuant()
{
	SetName(L"Particle");
	CreateRigidBody();
	SetPos(_vPos);
}

CParticle::CParticle(PARTICLE_TYPE _eType)
	: m_pTex(nullptr)
	, m_eType(_eType)
{
	SetName(L"Particle");
	CreateRigidBody();

	switch (_eType)
	{
	case PARTICLE_TYPE::bloodpool:
		m_pTex = CResMgr::GetInst()->LoadTexture(L"bloodpool", L"texture\\Particle\\effect_016_bloodpool.bmp");
		break;
	case PARTICLE_TYPE::bloodstain:
		m_pTex = CResMgr::GetInst()->LoadTexture(L"bloodpool", L"texture\\Particle\\effect_032_bloodstains.bmp");
		break;
	case PARTICLE_TYPE::bloodgibs:
		m_pTex = CResMgr::GetInst()->LoadTexture(L"bloodpool", L"texture\\Particle\\effect_030_bloodgibs.bmp");
		break;
	case PARTICLE_TYPE::bombradius:
		m_pTex = CResMgr::GetInst()->LoadTexture(L"bloodpool", L"texture\\Particle\\effect_017_bombradius.bmp");
		break;
	case PARTICLE_TYPE::END:
		break;
	default:
		break;
	}
}

CParticle::~CParticle()
{
}


void CParticle::update()
{
}

void CParticle::render(HDC _dc)
{
	int iWidth = static_cast<int>(m_pTex->GetWidth());
	int iHeight = static_cast<int>(m_pTex->GetHeight());


	TransparentBlt(_dc
		, static_cast<int>(GetPos().x - (iWidth / 2.f))
		, static_cast<int>(GetPos().y - (iHeight / 2.f))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, 32, 32
		, RGB(255, 0, 255));
}
