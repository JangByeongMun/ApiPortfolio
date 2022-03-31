#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class MenuLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MenuLevel();
	~MenuLevel();

	// delete Function
	MenuLevel(const MenuLevel& _Other) = delete;
	MenuLevel(MenuLevel&& _Other) noexcept = delete;
	MenuLevel& operator=(const MenuLevel& _Other) = delete;
	MenuLevel& operator=(MenuLevel&& _Other) noexcept = delete;


protected:
	void Loading() override;
	void Update() override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	int CurrentScreen_;
};

