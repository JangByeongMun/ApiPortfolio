#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class IntroPage : public GameEngineActor
{
public:
	// constrcuter destructer
	IntroPage();
	~IntroPage();

	// delete Function
	IntroPage(const IntroPage& _Other) = delete;
	IntroPage(IntroPage&& _Other) noexcept = delete;
	IntroPage& operator=(const IntroPage& _Other) = delete;
	IntroPage& operator=(IntroPage&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:

};