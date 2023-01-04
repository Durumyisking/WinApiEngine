#include "pch.h"
#include "SoundMgr.h"
#include "Core.h"

#include "Sound.h"
#include "PathMgr.h"

CSoundMgr::CSoundMgr()
{

}

CSoundMgr::~CSoundMgr()
{
	Safe_Delete_Map(m_mapSound);
}


void CSoundMgr::init()
{
	if (FAILED(DirectSoundCreate8(NULL, &mSoundDevice, NULL)))
	{
		MessageBox(NULL, L"사운드디바이스생성실패", L"SYSTEM ERROR", MB_OK);
	}

	// 사운드 디바이스 협조레벨 설정.
	HWND hWnd = CCore::GetInst()->GetMainHwnd();
	if (FAILED(mSoundDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag값 정리
	{
		MessageBox(NULL, L"사운드디바이스 협조레벨 설정", L"SYSTEM ERROR", MB_OK);
	}


	// 소리 추가
	//////////////////////////////////////////////////////////////////////////

	/////////bgm
	
	// intro
	addSound(L"intro", L"sound\\bgm\\intro.wav", true);
	addSound(L"introtostart", L"sound\\bgm\\titletostart.wav", false);

	// basement
	addSound(L"basement", L"sound\\bgm\\basement.wav", true);

	// cave
	addSound(L"cave_intro", L"sound\\bgm\\the-caves-intro.wav", false);
	addSound(L"cave", L"sound\\bgm\\the-caves.wav", true);

	// depth
	addSound(L"depth_intro", L"sound\\bgm\\the-depths-intro.wav", false);
	addSound(L"depth", L"sound\\bgm\\the-depths.wav", true);

	// boss fight
	addSound(L"boss", L"sound\\bgm\\basic boss fight.wav", true);
	addSound(L"bossend", L"sound\\bgm\\bossfightend.wav", false);

	// evilroom
	addSound(L"evilfind", L"sound\\bgm\\satanfind.wav", false);
	addSound(L"evilroom", L"sound\\bgm\\deal-with-the-devil.wav", true);

	// secret room
	addSound(L"secretfind", L"sound\\bgm\\secretfind.wav", false);
	addSound(L"secretroom", L"sound\\bgm\\secretroom.wav", true);

	// treasure room
	addSound(L"treasureroom", L"sound\\bgm\\treasure room.wav", false);

	//////////

	// isaac
	addSound(L"isaachurt1", L"sound\\isaac\\hurt grunt.wav", false);
	addSound(L"isaachurt2", L"sound\\isaac\\hurt grunt1.wav", false);
	addSound(L"isaachurt3", L"sound\\isaac\\hurt grunt2.wav", false);
	addSound(L"itemget", L"sound\\isaac\\power up1.wav", false);

	// tear
	addSound(L"tearfire1", L"sound\\tear fire 4.wav", false);
	addSound(L"tearfire2", L"sound\\tear fire 5.wav", false);
	addSound(L"teardeath", L"sound\\tear block.wav", false);
	
	// pickup
	addSound(L"soulheartget", L"sound\\pickup\\holy.wav", false);
	addSound(L"keyget", L"sound\\pickup\\key pickup guantlet 4.wav", false);
	addSound(L"coindrop", L"sound\\pickup\\penny drop 1.wav", false);
	addSound(L"coinget", L"sound\\pickup\\penny pickup 1.wav", false);
	addSound(L"heartget", L"sound\\pickup\\vamp.wav", false);
	
	// door
	addSound(L"doorunlock", L"sound\\unlock.wav", false);
	addSound(L"dooropen", L"sound\\door heavy open.wav", false);

	
	// explosion
	addSound(L"explosion", L"sound\\explosions.wav", false);
	
	// props
	addSound(L"fireburn", L"sound\\props\\fire burning.wav", true);
	addSound(L"firedeath", L"sound\\props\\firedeath hiss.wav", false);
	addSound(L"popdeath", L"sound\\props\\plop.wav", false);
	addSound(L"rockdeath", L"sound\\props\\rock crumble 0.wav", false);

	////////////////////////////////////////////////////////////////////////////////
}

void CSoundMgr::Play(wstring _strname)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strname);

	if (iter == m_mapSound.end())
	{
		// 찾는 소리 없으면 오류
		assert(true);
	}

	iter->second->Play(iter->second->IsLoop());

}

void CSoundMgr::Stop(wstring _strname, bool _bReset)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strname);

	if (iter == m_mapSound.end())
		assert(true);

	iter->second->Stop(_bReset);
}

bool CSoundMgr::IsPlaying(wstring _strname)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strname);

	if (iter == m_mapSound.end())
		assert(true);

	return 	!(iter->second->IsEnd());
}

int CSoundMgr::GetVolume(wstring _strName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strName);

	if (iter == m_mapSound.end())
		assert(true);

	return 	iter->second->GetVolume();
}

void CSoundMgr::addSound(wstring _strname, wstring _strpath, bool loop)
{
	CSound* pSound = new CSound();
	pSound->SetName(_strname);
	wstring strFolder = CPathMgr::GetInst()->GetContentPath();
	strFolder += _strpath;
	pSound->Load(strFolder);
	m_mapSound.insert(make_pair(pSound->GetName(), pSound));
	pSound->SetLoop(loop);
}
