#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
class OptionWindow : public	GameEngineActor
{
public:
	// constrcuter destructer
	OptionWindow();
	~OptionWindow();

	// delete Function
	OptionWindow(const OptionWindow& _Other) = delete;
	OptionWindow(OptionWindow&& _Other) noexcept = delete;
	OptionWindow& operator=(const OptionWindow& _Other) = delete;
	OptionWindow& operator=(OptionWindow&& _Other) noexcept = delete;

protected: 

private:

};

