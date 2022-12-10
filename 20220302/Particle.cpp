#include "pch.h"
#include "Particle.h"

#include "RigidBody.h"
#include "Texture.h"
#include "ResMgr.h"


CParticle::CParticle(Vec2 _vPos, PARTICLE_TYPE _eType)
	: m_pTex(nullptr)
	, m_eType(_eType)
	, m_vSliceQuant()
	, m_vSlice()
	, m_vSliceGap()
{
	SetName(L"Particle");
	CreateRigidBody();
	SetPos(_vPos);
}

CParticle::CParticle(PARTICLE_TYPE _eType)
	: m_pTex(nullptr)
	, m_eType(_eType)
	, m_vSliceQuant()
	, m_vSlice()
	, m_vSliceGap()
{
	SetName(L"Particle");
	CreateRigidBody();

	switch (_eType)
	{
	case PARTICLE_TYPE::bloodpool:
		m_pTex = CResMgr::GetInst()->LoadTexture(L"bloodpool", L"texture\\Particle\\effect_016_bloodpool.bmp");
		{
			void* p = new int();
			srand((int)p);
			int size = rand() % 3;

			switch (size)
			{
			case 0:
				m_vSliceQuant = Vec2(32.f, 32.f);
				m_vSlice.x = rand() % 2;
				m_vSlice.y = rand() % 6;
				SetScale(Vec2(32.f, 32.f));
				break;
			case 1:
				m_vSliceQuant = Vec2(48.f, 48.f);
				m_vSliceGap = Vec2(64.f, 0.f);
				m_vSlice.x = rand() % 2;
				m_vSlice.y = rand() % 3;
				SetScale(Vec2(48.f, 48.f));
				break;
			case 2:
				m_vSliceQuant = Vec2(96.f, 96.f);
				m_vSliceGap = Vec2(160.f, 0.f);
				m_vSlice.x = rand() % 3;
				m_vSlice.y = rand() % 2;
				SetScale(Vec2(96.f, 96.f));
				break;
			default:
				break;
			}
			delete p;
		}
		break;
	case PARTICLE_TYPE::bloodstain:
		m_pTex = CResMgr::GetInst()->LoadTexture(L"bloodstain", L"texture\\Particle\\effect_032_bloodstains.bmp");
		{
			void* p = new int();
			srand((int)p);
			delete p;
		}
		break;
		 
	case PARTICLE_TYPE::bloodgibs:
		m_pTex = CResMgr::GetInst()->LoadTexture(L"bloodgibs", L"texture\\Particle\\effect_030_bloodgibs.bmp");
		SetScale(Vec2(16.f, 16.f));
		{
			void* p = new int();
			srand((int)p);
			int size = rand() % 3;

			switch (size)
			{
			case 0:
				m_vSliceQuant = Vec2(16.f, 16.f);
				m_vSlice.x = rand() % 4;
				m_vSlice.y = rand() % 3;
				break;
			case 1:
				m_vSliceQuant = Vec2(16.f, 16.f);
				m_vSliceGap = Vec2(32.f, 48.f);
				m_vSlice.x = rand() % 2;
				m_vSlice.y = rand() % 1;
				break;
			case 2:
				m_vSliceQuant = Vec2(4.f, 4.f);
				m_vSliceGap = Vec2(160.f, 0.f);
				m_vSlice.x = rand() % 8;
				m_vSlice.y = rand() % 2;
				SetScale(Vec2(4.f, 4.f));
				break;
			default:
				break;
			}
			delete p;
		}

		break;
	case PARTICLE_TYPE::bombradius:
		m_pTex = CResMgr::GetInst()->LoadTexture(L"bombradius", L"texture\\Particle\\effect_017_bombradius.bmp");
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
	Vec2 vScale = GetScale();
	Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);


	TransparentBlt(_dc
		, static_cast<int>(vPos.x - (vScale.x / 2))
		, static_cast<int>(vPos.y - (vScale.y / 2))
		, static_cast<int>(vScale.x * 2), static_cast<int>(vScale.y * 2)
		, m_pTex->GetDC()
		, m_vSliceGap.x + (m_vSlice.x * m_vSliceQuant.x)
		, m_vSliceGap.y + (m_vSlice.y * m_vSliceQuant.y)
		, m_vSliceQuant.x, m_vSliceQuant.y
		, RGB(255, 0, 255));

}
