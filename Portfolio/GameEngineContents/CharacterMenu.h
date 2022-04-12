#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>

class CharacterValue
{
public:
	int Hp;
	int Speed;
	int Attack;
	int Item;

	CharacterValue(int _Hp, int _Speed, int _Attack, int _Item)
	{
		Hp = _Hp;
		Speed = _Speed;
		Attack = _Attack;
		Item = _Item;
	}
};

// Ό³Έν :
class CharacterMenu : public GameEngineActor
{
public:
	// constrcuter destructer
	CharacterMenu();
	~CharacterMenu();

	// delete Function
	CharacterMenu(const CharacterMenu& _Other) = delete;
	CharacterMenu(CharacterMenu&& _Other) noexcept = delete;
	CharacterMenu& operator=(const CharacterMenu& _Other) = delete;
	CharacterMenu& operator=(CharacterMenu&& _Other) noexcept = delete;

	void ChangeIndex(int _Index);
	void AddIndex(int _Index);

	void ChangeDifficult(int _Difficult);
	void AddDifficult(int _Difficult);

	void SelectIndex();

protected:

private:
	std::vector<GameEngineRenderer*> AllCharacters_;
	std::vector<GameEngineRenderer*> AllCharactersName_;
	std::vector<CharacterValue> AllState_;
	std::vector<float4> AllPose_;
	int CurrentIndex_;

	std::vector<GameEngineRenderer*> StateHp_;
	std::vector<GameEngineRenderer*> StateSpeed_;
	std::vector<GameEngineRenderer*> StateAttack_;
	std::vector<GameEngineRenderer*> StateItem_;

	std::vector<float4> DifficultyArrowPos_;
	GameEngineRenderer* DifficultyArrow_;
	GameEngineRenderer* HardRenderer_;
	int CurrentDifficulty_;

	void Start() override;
	void UpdateUI();
};

