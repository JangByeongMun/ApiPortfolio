#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class LoadingAnim2 : public GameEngineActor
{
public:
	// constrcuter destructer
	LoadingAnim2();
	~LoadingAnim2();

	// delete Function
	LoadingAnim2(const LoadingAnim2& _Other) = delete;
	LoadingAnim2(LoadingAnim2&& _Other) noexcept = delete;
	LoadingAnim2& operator=(const LoadingAnim2& _Other) = delete;
	LoadingAnim2& operator=(LoadingAnim2&& _Other) noexcept = delete;

protected:

private:
	std::vector<GameEngineRenderer*> RendererVector_;
	GameEngineRenderer* BallRenderer_;
	float AnimTimer_;

	void Start() override;
	void Update() override;
};

