#pragma once

class CSound;

class CSoundMgr
{
	SINGLE(CSoundMgr);

public:
	void init();
	LPDIRECTSOUND8 GetDevice() const { return mSoundDevice; }
	void Play(wstring _strname);
	void Stop(wstring _strname, bool _bReset);

	bool IsPlaying(wstring _strname);

	int GetVolume(wstring _strName);


private:
	void addSound(wstring _strname, wstring _strpath, bool loop);

private:
	LPDIRECTSOUND8 mSoundDevice;

	map<wstring, CSound*> m_mapSound;

};

