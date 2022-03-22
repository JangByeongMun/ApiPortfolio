#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class TitleForeGround : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleForeGround();
	~TitleForeGround();

	// delete Function
	TitleForeGround(const TitleForeGround& _Other) = delete;
	TitleForeGround(TitleForeGround&& _Other) noexcept = delete;
	TitleForeGround& operator=(const TitleForeGround& _Other) = delete;
	TitleForeGround& operator=(TitleForeGround&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

