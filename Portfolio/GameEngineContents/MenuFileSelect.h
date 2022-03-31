#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class MenuFileSelect : public GameEngineActor
{
public:
	// constrcuter destructer
	MenuFileSelect();
	~MenuFileSelect();

	// delete Function
	MenuFileSelect(const MenuFileSelect& _Other) = delete;
	MenuFileSelect(MenuFileSelect&& _Other) noexcept = delete;
	MenuFileSelect& operator=(const MenuFileSelect& _Other) = delete;
	MenuFileSelect& operator=(MenuFileSelect&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
};

