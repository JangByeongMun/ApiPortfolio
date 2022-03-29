#pragma once
#include <GameEngine/GameEngineActor.h>

class Credit10 : public GameEngineActor
{
public:
	// constrcuter destructer
	Credit10();
	~Credit10();

	// delete Function
	Credit10(const Credit10& _Other) = delete;
	Credit10(Credit10&& _Other) noexcept = delete;
	Credit10& operator=(const Credit10& _Other) = delete;
	Credit10& operator=(Credit10&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

