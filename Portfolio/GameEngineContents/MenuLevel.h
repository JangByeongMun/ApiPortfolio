#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <vector>

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

// ���� :
class MenuStart;
class MenuFileSelect;
class GameMenu;
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
	float CurrentLevelTime_;
	MenuStart* Index0_;
	MenuFileSelect* Index1_;
	GameMenu* Index2_;

	///////////////// ȭ�� ����
public:
	void ChangeIndex(int _Index);
	
private:
	std::vector<float4> AllScreenPos_;
	float4 CurrentPos_;
	float ChangeStartTime_;
	bool IsChanging_;
	int ChangeIndex_;
	int CurrentIndex_;
};

