#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>

enum class EndingState
{
	None,
	Ending1,
	Ending2,
	Ending3,
	Ending4,
	Ending5,
	Ending6,
	Ending7,
	Ending8,
	Ending9,
	Ending10,
	Ending11,
	Ending12,
	Ending13,
	Ending14,
	Ending15,
};

class EndingManager2 : public GameEngineActor
{
public:
	// constrcuter destructer
	EndingManager2();
	~EndingManager2();

	// delete Function
	EndingManager2(const EndingManager2& _Other) = delete;
	EndingManager2(EndingManager2&& _Other) noexcept = delete;
	EndingManager2& operator=(const EndingManager2& _Other) = delete;
	EndingManager2& operator=(EndingManager2&& _Other) noexcept = delete;

protected:

private:
	std::vector<float> Timer_;
	EndingState CurrentState_;
	//float CurrentTime_;


	GameEngineRenderer* AnimationRenderer_;
	float AnimationStartTime_;

	void Start() override;
	void Update() override;
	void ChangeState(EndingState _State);

	void Ending1Start();
	void Ending2Start();
	void Ending3Start();
	void Ending4Start();
	void Ending5Start();
	void Ending6Start();
	void Ending7Start();
	void Ending8Start();
	void Ending9Start();
	void Ending10Start();
	void Ending11Start();
	void Ending12Start();
	void Ending13Start();
	void Ending14Start();
	void Ending15Start();

	void Ending1Update();
	void Ending2Update();
	void Ending3Update();
	void Ending4Update();
	void Ending5Update();
	void Ending6Update();
	void Ending7Update();
	void Ending8Update();
	void Ending9Update();
	void Ending10Update();
	void Ending11Update();
	void Ending12Update();
	void Ending13Update();
	void Ending14Update();
	void Ending15Update();
};

