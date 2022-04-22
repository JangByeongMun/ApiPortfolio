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

	inline void AddFireHP(float _Value)
	{
		FireHp_ += _Value;

		if (FireHp_ >= 10.0f)
		{
			Renderer_->SetScale(float4(144.0f, 144.0f));
		}
		else if (FireHp_ >= 6.0f)
		{
			Renderer_->SetScale(float4(144.0f, 144.0f) * 0.7f);
		}
		else
		{
			Renderer_->SetScale(float4(144.0f, 144.0f) * 0.5f);
		}


		if (FireHp_ <= 0.0f)
		{
			FireHp_ = 0.0f;

			for (int i = 0; i < FirePlaceRenderer_.size(); i++)
			{
				FirePlaceRenderer_[i]->ChangeAnimation("grid_fireplace_Off");
			}

			Renderer_->Off();
			Collision_->Off();
		}
	}
	
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
};

