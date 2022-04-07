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

// 설명 :
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

	///////////////// 화면 변경
public:
	void UpdateScreen();
	void ChangeScreen();

	void StayStart();
	void StayUpdate();

	void ChangeStart(int _Index);
	void ChangeUpdate();
	
private:
	std::vector<float4> AllScreenPos_;
	float4 CurrentPos_;
	float ChangeStartTime_;
	bool IsChanging_;
	int ChangeIndex_;
	int CurrentIndex_;
};

