#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>
#include "ContentsEnum.h"

// 설명 : 좌하단 장신구UI
class AccessoryUI : public GameEngineActor
{
public:
	// constrcuter destructer
	AccessoryUI();
	~AccessoryUI();

	// delete Function
	AccessoryUI(const AccessoryUI& _Other) = delete;
	AccessoryUI(AccessoryUI&& _Other) noexcept = delete;
	AccessoryUI& operator=(const AccessoryUI& _Other) = delete;
	AccessoryUI& operator=(AccessoryUI&& _Other) noexcept = delete;

	void SetAccessory(AccessoryType _Type);

protected:

private:
	std::vector<GameEngineRenderer*> RendererVector_;

	void Start() override;
	void Update() override;
};

