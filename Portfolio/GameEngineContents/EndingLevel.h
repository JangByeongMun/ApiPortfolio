#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
#include <vector>

// Ό³Έν :
class EndingManager;
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
	std::vector<float> AllTimer_;
	float PrevTime_;
	int CurrentIndex_;
	EndingManager* EndingPtr_;

	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	float CurrentTimer(int _Index);
};

