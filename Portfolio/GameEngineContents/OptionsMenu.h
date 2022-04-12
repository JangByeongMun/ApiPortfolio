#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class OptionsMenu : public GameEngineActor
{
public:
	// constrcuter destructer
	OptionsMenu();
	~OptionsMenu();

	// delete Function
	OptionsMenu(const OptionsMenu& _Other) = delete;
	OptionsMenu(OptionsMenu&& _Other) noexcept = delete;
	OptionsMenu& operator=(const OptionsMenu& _Other) = delete;
	OptionsMenu& operator=(OptionsMenu&& _Other) noexcept = delete;

protected:

private:

	void Start() override;
};

