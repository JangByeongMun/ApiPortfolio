#pragma once
#include <GameEngine/GameEngineActor.h>

enum class BoxType
{
	Normal,
	Gold,
};

// Ό³Έν :
class BoxItem : public GameEngineActor
{
public:
	// constrcuter destructer
	BoxItem();
	~BoxItem();

	// delete Function
	BoxItem(const BoxItem& _Other) = delete;
	BoxItem(BoxItem&& _Other) noexcept = delete;
	BoxItem& operator=(const BoxItem& _Other) = delete;
	BoxItem& operator=(BoxItem&& _Other) noexcept = delete;

	void SetType(BoxType _Type);

protected:

private:
	std::vector<GameEngineRenderer*> RendererVector_;
	GameEngineCollision* Collision_;
	BoxType Type_;

	void Start();
	void Update();
};

