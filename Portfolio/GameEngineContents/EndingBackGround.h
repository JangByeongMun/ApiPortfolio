#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class EndingBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	EndingBackGround();
	~EndingBackGround();

	// delete Function
	EndingBackGround(const EndingBackGround& _Other) = delete;
	EndingBackGround(EndingBackGround&& _Other) noexcept = delete;
	EndingBackGround& operator=(const EndingBackGround& _Other) = delete;
	EndingBackGround& operator=(EndingBackGround&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

