#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>

// Ό³Έν :
class RandomMenuLoading : public GameEngineActor
{
public:
	// constrcuter destructer
	RandomMenuLoading();
	~RandomMenuLoading();

	// delete Function
	RandomMenuLoading(const RandomMenuLoading& _Other) = delete;
	RandomMenuLoading(RandomMenuLoading&& _Other) noexcept = delete;
	RandomMenuLoading& operator=(const RandomMenuLoading& _Other) = delete;
	RandomMenuLoading& operator=(RandomMenuLoading&& _Other) noexcept = delete;
	
	void RandomLoading();

protected:

private:
	std::vector<GameEngineRenderer*> LoadingRenderers_;
	void Start() override;
};

