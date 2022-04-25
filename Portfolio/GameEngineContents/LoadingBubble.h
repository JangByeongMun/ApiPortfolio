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

private:
	std::vector<GameEngineRenderer*> RendererVector;
	float AnimTimer_;
	bool CreateNightmare;

	void Start() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
};

