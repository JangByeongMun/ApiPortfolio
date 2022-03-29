#pragma once
#include <GameEngine/GameEngineActor.h>

class Credit09 : public GameEngineActor
{
public:
	// constrcuter destructer
	Credit09();
	~Credit09();

	// delete Function
	Credit09(const Credit09& _Other) = delete;
	Credit09(Credit09&& _Other) noexcept = delete;
	Credit09& operator=(const Credit09& _Other) = delete;
	Credit09& operator=(Credit09&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

