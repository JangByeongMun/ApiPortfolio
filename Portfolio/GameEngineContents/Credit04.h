#pragma once
#include <GameEngine/GameEngineActor.h>

class Credit04 : public GameEngineActor
{
public:
	// constrcuter destructer
	Credit04();
	~Credit04();

	// delete Function
	Credit04(const Credit04& _Other) = delete;
	Credit04(Credit04&& _Other) noexcept = delete;
	Credit04& operator=(const Credit04& _Other) = delete;
	Credit04& operator=(Credit04&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

