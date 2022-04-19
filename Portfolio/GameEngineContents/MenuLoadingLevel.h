#pragma once
#include <GameEngine/GameEngineLevel.h>

class RandomMenuLoading;
class MenuLoadingLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MenuLoadingLevel();
	~MenuLoadingLevel();

	// delete Function
	MenuLoadingLevel(const MenuLoadingLevel& _Other) = delete;
	MenuLoadingLevel(MenuLoadingLevel&& _Other) noexcept = delete;
	MenuLoadingLevel& operator=(const MenuLoadingLevel& _Other) = delete;
	MenuLoadingLevel& operator=(MenuLoadingLevel&& _Other) noexcept = delete;

protected:

private:
	RandomMenuLoading* Loading_;
	float LoadingTimer_;

	void Loading() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

};

