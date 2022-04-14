#pragma once
#include "GameEngineNameObject.h"
#include "ThirdParty/inc/fmod.hpp"
#include <map>

class GameEngineSoundPlayer;
// ���� :
class GameEngineSound : public GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineSound();
	~GameEngineSound();

	// delete Function
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

protected:
	bool Load(const std::string& _Path);

private:
	FMOD::Sound* Sound;

	///////////////////////////////////////// �Ŵ�����Ʈ ���� ���
public:
	static GameEngineSoundPlayer SoundPlayControl(const std::string& _Name);
	static GameEngineSoundPlayer SoundPlayControlOneShot(const std::string& _Name); // �ѹ��� �����ϸ鼭 �����ϴ� �÷��̾� ����

	static void SoundPlayOneShot(const std::string& _Name, int _LoopCount = 0);
	static void Update();

////////////////////////////////////////// ���ҽ� �Ŵ�����Ʈ
public:
	static GameEngineSound* FindRes(const std::string& _Name);
	static GameEngineSound* LoadRes(const std::string& _Path);
	static GameEngineSound* LoadRes(const std::string& _Path, const std::string& _Name);

	static void AllResourcesDestroy();

private:
	static std::map<std::string, GameEngineSound*> AllRes;

};

// ���� ����� �����Ҽ� �ִ� ��ɵ��� �����̴ϴ�.
class GameEngineSound;
class GameEngineSoundPlayer 
{
	friend GameEngineSound;

public:
	void Play();
	void Stop();
	void SetVolume(float _Volume);

	GameEngineSoundPlayer();
	GameEngineSoundPlayer(const GameEngineSoundPlayer& _Other);
	~GameEngineSoundPlayer();

private:
	GameEngineSound* Sound_;
	FMOD::Channel* ControlHandle_;

	GameEngineSoundPlayer(GameEngineSound* Sound, FMOD::Channel* ControlHandle);
};