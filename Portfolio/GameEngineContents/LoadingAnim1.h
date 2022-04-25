#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class LoadingAnim1 : public GameEngineActor
{
public:
	// constrcuter destructer
	LoadingAnim1();
	~LoadingAnim1();

	// delete Function
	LoadingAnim1(const LoadingAnim1& _Other) = delete;
	LoadingAnim1(LoadingAnim1&& _Other) noexcept = delete;
	LoadingAnim1& operator=(const LoadingAnim1& _Other) = delete;
	LoadingAnim1& operator=(LoadingAnim1&& _Other) noexcept = delete;

protected:

private:
	std::vector<GameEngineRenderer*> RendererVector_;
	float AnimTimer_;

	void Start() override;
	void Update() override;
};

