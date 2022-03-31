#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class MenuStart : public GameEngineActor
{
public:
	// constrcuter destructer
	MenuStart();
	~MenuStart();

	// delete Function
	MenuStart(const MenuStart& _Other) = delete;
	MenuStart(MenuStart&& _Other) noexcept = delete;
	MenuStart& operator=(const MenuStart& _Other) = delete;
	MenuStart& operator=(MenuStart&& _Other) noexcept = delete;

protected:
	
private:
	void Start() override;
	void Update() override;
};

