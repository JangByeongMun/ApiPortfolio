#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <vector>

// Ό³Έν :
class EndingLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	EndingLevel();
	~EndingLevel();

	// delete Function
	EndingLevel(const EndingLevel& _Other) = delete;
	EndingLevel(EndingLevel&& _Other) noexcept = delete;
	EndingLevel& operator=(const EndingLevel& _Other) = delete;
	EndingLevel& operator=(EndingLevel&& _Other) noexcept = delete;

	inline void ChangeEndingCredit(int _Index)
	{
		CurrentIndex_ = _Index;
	}

protected:

private:
	std::vector<GameEngineActor*> AllActors_;
	float LevelTime_;
	int CurrentIndex_;

	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;
};

