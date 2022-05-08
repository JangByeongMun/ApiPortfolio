#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>

// ���� :
class Player;
class PlayLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

	void CameraLerp(float4 _Start, float4 _Goal);
	void StopBGM();
	void StopBossBGM();
	void PlayBossBGM();

	GameEngineActor* GlobalActor;

protected:
	void Loading() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	GameEngineSoundPlayer BgmPlayer_;
	GameEngineSoundPlayer BossBgmPlayer_;

	// ī�޶� �����̵�
	bool IsLerp_;
	float LerpTimer_;
	float4 Start_;
	float4 Goal_;
};

