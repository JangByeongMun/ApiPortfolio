#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class LoadingPage : public GameEngineActor
{
public:
	// constrcuter destructer
	LoadingPage();
	~LoadingPage();

	// delete Function
	LoadingPage(const LoadingPage& _Other) = delete;
	LoadingPage(LoadingPage&& _Other) noexcept = delete;
	LoadingPage& operator=(const LoadingPage& _Other) = delete;
	LoadingPage& operator=(LoadingPage&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

