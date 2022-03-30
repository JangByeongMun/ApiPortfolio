#pragma once
#include <GameEngine/GameEngineActor.h>

class Credit13 : public GameEngineActor
{
public:
	// constrcuter destructer
	Credit13();
	~Credit13();

	// delete Function
	Credit13(const Credit13& _Other) = delete;
	Credit13(Credit13&& _Other) noexcept = delete;
	Credit13& operator=(const Credit13& _Other) = delete;
	Credit13& operator=(Credit13&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* BookRenderer_;
	float ActorTime_;

	void Start() override;
	void Update() override;
};

