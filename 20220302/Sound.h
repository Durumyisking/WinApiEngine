#pragma once
class CSound
{

public:
	HRESULT Load(const wstring& path);
	bool LoadWavFile(const std::wstring& path);
	void Play(bool loop);
	void Stop(bool reset);
	void SetPosition(float position, bool loop);
	void SetVolume(float volume);
	float GetVolume() const { return volume_return; }
	int GetDecibel(float volume);

	void SetName(wstring _strName) { mstrName = _strName; }
	wstring GetName() const { return mstrName; }
	bool IsLoop() const { return mLoop; }
	void SetLoop(bool _bFlag) { mLoop = _bFlag; }

	bool IsEnd() const { return mEnd; }


private:
	LPDIRECTSOUNDBUFFER		mSoundBuffer;
	DSBUFFERDESC			mBufferDesc;
	int mVolume;
	float volume_return;
	wstring mstrName;
	bool mLoop;
	bool mEnd;
};

