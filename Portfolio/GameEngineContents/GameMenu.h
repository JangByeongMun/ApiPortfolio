#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include <GameEngine/GameEngineRenderer.h>

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

	inline void ChangeMenuIndex(int _Index) 
	{
		if (CurrentIndex_ < 0)
		{
			CurrentIndex_ = 0;
		}
		if (CurrentIndex_ > 2)
		{
			CurrentIndex_ = 2;
		}

		CurrentIndex_ = _Index;
		ArrowRenderer_->SetPivot(ArrowPos_[CurrentIndex_]);
	}
	inline void AddMenuIndex(int _Index)
	{
		if (CurrentIndex_ < 0)
		{
			CurrentIndex_ = 0;
		}
		if (CurrentIndex_ > 2)
		{
			CurrentIndex_ = 2;
		}

		CurrentIndex_ += _Index;
		ArrowRenderer_->SetPivot(ArrowPos_[CurrentIndex_]);
	}

	void SelectMenu();

protected:

private:
	std::vector<float4> ArrowPos_;
	GameEngineRenderer* ArrowRenderer_;
	int CurrentIndex_;

	void Start() override;
};

