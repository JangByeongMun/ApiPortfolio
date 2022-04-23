#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>
#include "ContentsEnum.h"
#include "ContentsGlobal.h"

// Ό³Έν :
class EnterBossRoom : public GameEngineActor
{
public:
	// constrcuter destructer
	EnterBossRoom();
	~EnterBossRoom();

	// delete Function
	EnterBossRoom(const EnterBossRoom& _Other) = delete;
	EnterBossRoom(EnterBossRoom&& _Other) noexcept = delete;
	EnterBossRoom& operator=(const EnterBossRoom& _Other) = delete;
	EnterBossRoom& operator=(EnterBossRoom&& _Other) noexcept = delete;

	void Setting();
protected:

private:
	std::vector<GameEngineRenderer*> PlayerRenderers_;
	std::vector<GameEngineRenderer*> BossRenderers_;
	float AnimTimer_;

	void Start() override;
	void Update() override;
};

