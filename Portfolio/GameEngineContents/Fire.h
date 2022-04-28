#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class Fire : public GameEngineActor
{
public:
	// constrcuter destructer
	Fire();
	~Fire();

	// delete Function
	Fire(const Fire& _Other) = delete;
	Fire(Fire&& _Other) noexcept = delete;
	Fire& operator=(const Fire& _Other) = delete;
	Fire& operator=(Fire&& _Other) noexcept = delete;

	void AddFireHP(float _Value);
	inline float GetFireHP()
	{
		return FireHp_;
	}

protected:

private:
	std::vector<GameEngineRenderer*> FirePlaceRenderer_;
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	float FireHp_;

	void Start() override;
	void Update() override;
	void RandomDrop();
};

