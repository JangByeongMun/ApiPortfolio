#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class LoadingCharacter : public GameEngineActor
{
public:
	// constrcuter destructer
	LoadingCharacter();
	~LoadingCharacter();

	// delete Function
	LoadingCharacter(const LoadingCharacter& _Other) = delete;
	LoadingCharacter(LoadingCharacter&& _Other) noexcept = delete;
	LoadingCharacter& operator=(const LoadingCharacter& _Other) = delete;
	LoadingCharacter& operator=(LoadingCharacter&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
	float StartX;
	bool IsLeft;
};

