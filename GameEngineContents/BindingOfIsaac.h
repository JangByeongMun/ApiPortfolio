#pragma once
#include <GameEngine/GameEngine.h>


// Ό³Έν :
class BindingOfIsaac : public GameEngine
{
public:
	// constrcuter destructer
	BindingOfIsaac();
	~BindingOfIsaac();

	// delete Function
	BindingOfIsaac(const BindingOfIsaac& _Other) = delete;
	BindingOfIsaac(BindingOfIsaac&& _Other) noexcept = delete;
	BindingOfIsaac& operator=(const BindingOfIsaac& _Other) = delete;
	BindingOfIsaac& operator=(BindingOfIsaac&& _Other) noexcept = delete;

	void GameInit() override;
	void GameLoop() override;
	void GameEnd() override;
protected:

private:

};

