#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class LoadingBubble : public GameEngineActor
{
public:
	// constrcuter destructer
	LoadingBubble();
	~LoadingBubble();

	// delete Function
	LoadingBubble(const LoadingBubble& _Other) = delete;
	LoadingBubble(LoadingBubble&& _Other) noexcept = delete;
	LoadingBubble& operator=(const LoadingBubble& _Other) = delete;
	LoadingBubble& operator=(LoadingBubble&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

