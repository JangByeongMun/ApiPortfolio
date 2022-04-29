#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineSound.h>

// Ό³Έν :
class RoomActor;
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
	void SetRoom(RoomActor* _Room);

protected:

private:
	RoomActor* Room_;
	std::vector<GameEngineRenderer*> FirePlaceRenderer_;
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	float FireHp_;
	GameEngineSoundPlayer BGMPlayer_;

	void Start() override;
	void Update() override;
	void RandomDrop();
};

