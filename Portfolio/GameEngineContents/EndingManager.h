#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>

// Ό³Έν :
class EndingManager : public GameEngineActor
{
public:
	// constrcuter destructer
	EndingManager();
	~EndingManager();

	// delete Function
	EndingManager(const EndingManager& _Other) = delete;
	EndingManager(EndingManager&& _Other) noexcept = delete;
	EndingManager& operator=(const EndingManager& _Other) = delete;
	EndingManager& operator=(EndingManager&& _Other) noexcept = delete;

protected:

private:
	float CurrentTime_;
	std::vector<bool> CurrentCheck_;
	std::vector<float> Timer_;
	
	GameEngineRenderer* AnimationRenderer_;
	float AnimationStartTime_;

	void Start() override;
	void Update() override;
	float CurrentTimer(int _Index);
	bool IsStart(int _Index);
	bool IsUpdate(int _Index);
};

