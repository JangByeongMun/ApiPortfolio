#pragma once
#include <GameEngine/GameEngineActor.h>

class Credit06 : public GameEngineActor
{
public:
	// constrcuter destructer
	Credit06();
	~Credit06();

	// delete Function
	Credit06(const Credit06& _Other) = delete;
	Credit06(Credit06&& _Other) noexcept = delete;
	Credit06& operator=(const Credit06& _Other) = delete;
	Credit06& operator=(Credit06&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

