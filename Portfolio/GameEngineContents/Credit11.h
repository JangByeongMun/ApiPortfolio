#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class Credit11 : public GameEngineActor
{
public:
	// constrcuter destructer
	Credit11();
	~Credit11();

	// delete Function
	Credit11(const Credit11& _Other) = delete;
	Credit11(Credit11&& _Other) noexcept = delete;
	Credit11& operator=(const Credit11& _Other) = delete;
	Credit11& operator=(Credit11&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* BookRenderer_;
	float ActorTime_;

	void Start() override;
	void Update() override;
};

