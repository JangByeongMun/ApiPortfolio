#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// Ό³Έν :
class Stone : public GameEngineActor
{
public:
	// constrcuter destructer
	Stone();
	~Stone();

	// delete Function
	Stone(const Stone& _Other) = delete;
	Stone(Stone&& _Other) noexcept = delete;
	Stone& operator=(const Stone& _Other) = delete;
	Stone& operator=(Stone&& _Other) noexcept = delete;

	void BombStone();

protected:

private:
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;

	void Start() override;
};

