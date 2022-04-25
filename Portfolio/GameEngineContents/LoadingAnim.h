#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class LoadingAnim : public GameEngineActor
{
public:
	// constrcuter destructer
	LoadingAnim();
	~LoadingAnim();

	// delete Function
	LoadingAnim(const LoadingAnim& _Other) = delete;
	LoadingAnim(LoadingAnim&& _Other) noexcept = delete;
	LoadingAnim& operator=(const LoadingAnim& _Other) = delete;
	LoadingAnim& operator=(LoadingAnim&& _Other) noexcept = delete;

protected:

private:

};

