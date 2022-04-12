#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class StatsMenu : public GameEngineActor
{
public:
	// constrcuter destructer
	StatsMenu();
	~StatsMenu();

	// delete Function
	StatsMenu(const StatsMenu& _Other) = delete;
	StatsMenu(StatsMenu&& _Other) noexcept = delete;
	StatsMenu& operator=(const StatsMenu& _Other) = delete;
	StatsMenu& operator=(StatsMenu&& _Other) noexcept = delete;

protected:

private:

	void Start() override;

};

