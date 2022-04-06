#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class PlayBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayBackGround();
	~PlayBackGround();

	// delete Function
	PlayBackGround(const PlayBackGround& _Other) = delete;
	PlayBackGround(PlayBackGround&& _Other) noexcept = delete;
	PlayBackGround& operator=(const PlayBackGround& _Other) = delete;
	PlayBackGround& operator=(PlayBackGround&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

