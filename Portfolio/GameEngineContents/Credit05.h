#pragma once
#include <GameEngine/GameEngineActor.h>

class Credit05 : public GameEngineActor
{
public:
	// constrcuter destructer
	Credit05();
	~Credit05();

	// delete Function
	Credit05(const Credit05& _Other) = delete;
	Credit05(Credit05&& _Other) noexcept = delete;
	Credit05& operator=(const Credit05& _Other) = delete;
	Credit05& operator=(Credit05&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

