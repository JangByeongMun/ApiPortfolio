#pragma once
#include <GameEngine/GameEngineActor.h>

class Credit07 : public GameEngineActor
{
public:
	// constrcuter destructer
	Credit07();
	~Credit07();

	// delete Function
	Credit07(const Credit07& _Other) = delete;
	Credit07(Credit07&& _Other) noexcept = delete;
	Credit07& operator=(const Credit07& _Other) = delete;
	Credit07& operator=(Credit07&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

