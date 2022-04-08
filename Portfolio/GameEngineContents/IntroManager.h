#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>

// Ό³Έν :
class IntroManager : public GameEngineActor
{
public:
	// constrcuter destructer
	IntroManager();
	~IntroManager();

	// delete Function
	IntroManager(const IntroManager& _Other) = delete;
	IntroManager(IntroManager&& _Other) noexcept = delete;
	IntroManager& operator=(const IntroManager& _Other) = delete;
	IntroManager& operator=(IntroManager&& _Other) noexcept = delete;

protected:

private:
	float CurrentTime_;
	std::vector<bool> CurrentCheck_;
	std::vector<float> Timer_;

	void Start() override;
	void Update() override;
	float CurrentTimer(int _Index);
	bool IsStart(int _Index);
};

