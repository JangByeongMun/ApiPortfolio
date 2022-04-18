#pragma once
#include <GameEngine/GameEngineActor.h>

// 설명 : 우하단 알약, 카드 UI
// 폰트 필요할거같아서 우선 우선순위 뒤로 밀림
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

