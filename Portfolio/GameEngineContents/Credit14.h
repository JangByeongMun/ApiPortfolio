#pragma once
#include <GameEngine/GameEngineActor.h>

class Credit14 : public GameEngineActor
{
public:
	// constrcuter destructer
	Credit14();
	~Credit14();

	// delete Function
	Credit14(const Credit14& _Other) = delete;
	Credit14(Credit14&& _Other) noexcept = delete;
	Credit14& operator=(const Credit14& _Other) = delete;
	Credit14& operator=(Credit14&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

