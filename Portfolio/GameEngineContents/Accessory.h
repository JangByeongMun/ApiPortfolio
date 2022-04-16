#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>
#include "ContentsEnum.h"

// Ό³Έν :
class Accessory : public GameEngineActor
{
public:
	// constrcuter destructer
	Accessory();
	~Accessory();

	// delete Function
	Accessory(const Accessory& _Other) = delete;
	Accessory(Accessory&& _Other) noexcept = delete;
	Accessory& operator=(const Accessory& _Other) = delete;
	Accessory& operator=(Accessory&& _Other) noexcept = delete;

	inline void SetType(AccessoryType _Type)
	{
		Type_ = _Type;

		int SelectInt = static_cast<int>(_Type);
		for (int i = 0; i < RendererVector_.size(); i++)
		{
			if (SelectInt == i)
			{
				RendererVector_[i]->On();
			}
			else
			{
				RendererVector_[i]->Off();
			}
		}
	}
	inline AccessoryType GetType()
	{
		return Type_;
	}

protected:

private:
	std::vector<GameEngineRenderer*> RendererVector_;
	std::vector<std::string> NameVector_;
	GameEngineCollision* Collision_;
	AccessoryType Type_;

	void Start() override;
	void Update() override;
};

