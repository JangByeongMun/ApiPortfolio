#pragma once
#include <GameEngine/GameEngineActor.h>

class Credit08 : public GameEngineActor
{
public:
	// constrcuter destructer
	Credit08();
	~Credit08();

	// delete Function
	Credit08(const Credit08& _Other) = delete;
	Credit08(Credit08&& _Other) noexcept = delete;
	Credit08& operator=(const Credit08& _Other) = delete;
	Credit08& operator=(Credit08&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

