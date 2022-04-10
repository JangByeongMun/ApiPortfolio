#pragma once
#include <vector>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>

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
	
	void Play();

protected:

private:
	float CurrentTime_;
	std::vector<bool> CurrentCheck_;
	std::vector<float> Timer_;

	GameEngineSoundPlayer BgmPlayer_;
	GameEngineRenderer* AnimationRenderer1_;
	GameEngineRenderer* AnimationRenderer2_;
	float AnimationStartTime_;
	bool IsPlaying_;

	void Start() override;
	void Update() override;

	float CurrentTimer(int _Index);
	bool IsStart(int _Index);
	bool IsUpdate(int _Index);
	void Reset();
};