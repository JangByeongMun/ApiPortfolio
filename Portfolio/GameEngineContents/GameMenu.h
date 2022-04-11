#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameMenu : public GameEngineActor
{
public:
	// constrcuter destructer
	GameMenu();
	~GameMenu();

	// delete Function
	GameMenu(const GameMenu& _Other) = delete;
	GameMenu(GameMenu&& _Other) noexcept = delete;
	GameMenu& operator=(const GameMenu& _Other) = delete;
	GameMenu& operator=(GameMenu&& _Other) noexcept = delete;

protected:

private:

	void Start() override;
	void Update() override;
};

