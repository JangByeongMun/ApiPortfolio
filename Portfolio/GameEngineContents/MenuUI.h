#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class MenuUI : public GameEngineActor
{
public:
	// constrcuter destructer
	MenuUI();
	~MenuUI();

	// delete Function
	MenuUI(const MenuUI& _Other) = delete;
	MenuUI(MenuUI&& _Other) noexcept = delete;
	MenuUI& operator=(const MenuUI& _Other) = delete;
	MenuUI& operator=(MenuUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:

};

