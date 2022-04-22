#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <vector>
#include "ContentsEnum.h"

// ���� : Ư�� �ɷ��� ���� �нú� �����۵� �⺻
class PassiveItem : public GameEngineActor
{
public:
	// constrcuter destructer
	PassiveItem();
	~PassiveItem();

	// delete Function
	PassiveItem(const PassiveItem& _Other) = delete;
	PassiveItem(PassiveItem&& _Other) noexcept = delete;
	PassiveItem& operator=(const PassiveItem& _Other) = delete;
	PassiveItem& operator=(PassiveItem&& _Other) noexcept = delete;

	void Setting(PassiveType _Type);

protected:

private:
	std::vector<std::string> ItemNameVector_;
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	PassiveType Type_;

	float AnimTimer_;

	void Start() override;
	void Update() override;
};

