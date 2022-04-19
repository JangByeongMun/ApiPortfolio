#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <vector>
#include <GameEngineBase/GameEngineSound.h>

enum class MenuScreen
{
	MenuLogo = 0,
	FileSelect,
	GameMenu,
	CharacterMenu,
	Option,
};

enum class MenuStatue
{
	Stay,
	Moving, 
};

// 설명 :
class MenuStart;
class MenuFileSelect;
class GameMenu;
class CharacterMenu;
class StatsMenu;
class OptionsMenu;
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

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	float CurrentLevelTime_;
	MenuStart* Index0_;
	MenuFileSelect* Index1_;
	GameMenu* Index2_;
	CharacterMenu* Index3_;
	StatsMenu* Index4_;
	OptionsMenu* Index5_;

	///////////////// 화면 변경
public:
	void ChangeIndex(int _Index);
	void ChangeIndexImmediate(int _Index);
	
private:
	std::vector<float4> AllScreenPos_;
	float4 CurrentPos_;
	float ChangeStartTime_;
	bool IsChanging_;
	int ChangeIndex_;
	int CurrentIndex_;

	GameEngineSoundPlayer BgmPlayer_;
};

