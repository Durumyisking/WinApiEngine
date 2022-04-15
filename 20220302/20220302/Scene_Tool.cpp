#include "pch.h"
#include "Scene_Tool.h"

#include "Tile.h"

#include "ResMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

#include "UI.h"

#include "SelectGDI.h"

#include "resource.h"


CScene_Tool::CScene_Tool()
	: m_pTileTex(nullptr)
{

}


CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::update()
{
	CScene::update();


	SetTileIdx();



}

void CScene_Tool::render(HDC _dc)
{
	CSelectGDI pen(_dc, PEN_TYPE::GREEN);
	CSelectGDI brush(_dc, BRUSH_TYPE::WHITE);

	Rectangle(_dc, 0, 0, m_vResolution.x, m_vResolution.y);

	CScene::render(_dc);
}



void CScene_Tool::Enter()
{
	// 타일 생성
	CreateTile(4, 8);

	CUI* pUI = new CUI;
	pUI->SetScale(Vec2(500.f, 300.f));
	pUI->SetPos(Vec2(m_vResolution.x -pUI->GetScale().x, 0.f));

	CUI* pChildUI = new CUI;
	pChildUI->SetScale(Vec2(100.f, 50.f));
	pChildUI->SetPos(Vec2(0.f, 0.f));

	pUI->AddChild(pChildUI);

	AddObject(pUI, GROUP_TYPE::UI);



	CCamera::GetInst()->SetLookAt(m_vResolution / 2.f);
}

void CScene_Tool::Exit()
{
}

void CScene_Tool::SetTileIdx()
{
	Vec2 vMousePos = MOUSE_POS;

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

		UINT iTileX = (int)GetTileX();
		UINT iTileY = (int)GetTileY();

		// 음수시 오류니까 UINT 말고 int로 쓰자
		int iCol = (int)vMousePos.x / ROCK_SIZE;
		int iRow = (int)vMousePos.y / ROCK_SIZE;

		
		// bmp에서 넘어갔을때 동작 안되게 처리
		if (vMousePos.x < 0.f || iTileX <= iCol
			|| vMousePos.y < 0.f || iTileY <= iRow)
		{
			return;
		}

		UINT iIdx = iRow * iTileX + iCol;

		const vector <CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();
				

	}
}









// 전역함수 입니다
// Tile Count Window Proc
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{

			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// tool scene에서만 동작하는 함수니까 처리 해주자
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);
			


			// EndDialog의 두번째 인자는 dialogbox 함수 종료됐을때 결과값
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}