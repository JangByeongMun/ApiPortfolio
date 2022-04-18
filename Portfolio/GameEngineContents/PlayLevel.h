#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>

// 설명 :
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

protected:
	void Loading() override;
	void Update() override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	GameEngineSoundPlayer BgmPlayer_;

	// 카메라 보간이동
	bool IsLerp_;
	float LerpTimer_;
	float4 Start_;
	float4 Goal_;
};

