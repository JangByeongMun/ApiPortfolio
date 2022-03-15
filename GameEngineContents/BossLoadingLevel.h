#pragma once
#include "GameEngine/GameEngineLevel.h"

// Ό³Έν :
class BossLoadingLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BossLoadingLevel();
	~BossLoadingLevel();

	// delete Function
	BossLoadingLevel(const BossLoadingLevel& _Other) = delete;
	BossLoadingLevel(BossLoadingLevel&& _Other) noexcept = delete;
	BossLoadingLevel& operator=(const BossLoadingLevel& _Other) = delete;
	BossLoadingLevel& operator=(BossLoadingLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

	void SceneChangeStart() override;
	void SceneChangeEnd() override;

private:

};

enum class BossType
{
	MONSTRO,

	END,
};