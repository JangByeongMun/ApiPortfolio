#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>

// Ό³Έν :
class ItemUI : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemUI();
	~ItemUI();

	// delete Function
	ItemUI(const ItemUI& _Other) = delete;
	ItemUI(ItemUI&& _Other) noexcept = delete;
	ItemUI& operator=(const ItemUI& _Other) = delete;
	ItemUI& operator=(ItemUI&& _Other) noexcept = delete;

	void UpdateUI();

	void SetMoney(int _Value);
	void SetBomb(int _Value);
	void SetKey(int _Value, bool _IsMaster = false);

	void Reset();

protected:

private:
	GameEngineRenderer* MoneyRenderer_;
	GameEngineRenderer* BombRenderer_;
	GameEngineRenderer* KeyRenderer_;

	std::vector<GameEngineRenderer*> MoneyCount_;
	std::vector<GameEngineRenderer*> BombCount_;
	std::vector<GameEngineRenderer*> KeyCount_;

	int Money_;
	int Bomb_;
	int Key_;
	bool IsMasterKey_;

	void Start() override;
};

