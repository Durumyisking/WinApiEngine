#include "pch.h"
#include "Heart.h"

#include "ResMgr.h"
#include "Texture.h"

#include "Player.h"

CHeart::CHeart(int _iRenderGap, HEART_TYPE _eHeartType)
	: CUI(false)
	, m_eHeartType(_eHeartType)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"texheart", L"texture\\UI\\ui_hearts.bmp");

	switch (m_eHeartType)
	{
	case HEART_TYPE::NORMAL:
		SetScale(Vec2(16.f, 16.f));
		SetPos(Vec2(100.f + (32.f * _iRenderGap), 50.f));
		SetSlice({0.f, 0.f});
		break;
	case HEART_TYPE::SOUL:
		SetScale(Vec2(16.f, 16.f));
		SetPos(Vec2(100.f + (32.f * _iRenderGap), 80.f));
		SetSlice({ 0.f, 1.f });
		break;
	case HEART_TYPE::END:
		break;
	default:
		break;
	}
	
}

CHeart::~CHeart()
{
}

void CHeart::update()
{

}

void CHeart::render(HDC _dc)
{
	CUI::render(_dc);




}
