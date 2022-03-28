#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class HpUI : public GameEngineActor
{
public:
	// constrcuter destructer
	HpUI();
	~HpUI();

	// delete Function
	HpUI(const HpUI& _Other) = delete;
	HpUI(HpUI&& _Other) noexcept = delete;
	HpUI& operator=(const HpUI& _Other) = delete;
	HpUI& operator=(HpUI&& _Other) noexcept = delete;

protected:

private:

};

