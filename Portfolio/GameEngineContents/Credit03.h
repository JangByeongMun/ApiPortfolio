#pragma once
#include <GameEngine/GameEngineActor.h>

class Credit03 : public GameEngineActor
{
public:
	// constrcuter destructer
	Credit03();
	~Credit03();

	// delete Function
	Credit03(const Credit03& _Other) = delete;
	Credit03(Credit03&& _Other) noexcept = delete;
	Credit03& operator=(const Credit03& _Other) = delete;
	Credit03& operator=(Credit03&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

