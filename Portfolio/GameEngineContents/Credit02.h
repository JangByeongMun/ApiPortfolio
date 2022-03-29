#pragma once
#include <GameEngine/GameEngineActor.h>

class Credit02 : public GameEngineActor
{
public:
	// constrcuter destructer
	Credit02();
	~Credit02();

	// delete Function
	Credit02(const Credit02& _Other) = delete;
	Credit02(Credit02&& _Other) noexcept = delete;
	Credit02& operator=(const Credit02& _Other) = delete;
	Credit02& operator=(Credit02&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

