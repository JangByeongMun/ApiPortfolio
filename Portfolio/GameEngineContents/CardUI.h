#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� : ���ϴ� �˾�, ī�� UI
class CardUI : public GameEngineActor
{
public:
	// constrcuter destructer
	CardUI();
	~CardUI();

	// delete Function
	CardUI(const CardUI& _Other) = delete;
	CardUI(CardUI&& _Other) noexcept = delete;
	CardUI& operator=(const CardUI& _Other) = delete;
	CardUI& operator=(CardUI&& _Other) noexcept = delete;

protected:

private:
	

};

