#include "IntroManager.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

IntroManager::IntroManager() 
	: CurrentTime_(0)
	, CurrentCheck_({})
	, Timer_({})
{
}

IntroManager::~IntroManager() 
{
}

void IntroManager::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CurrentTime_ = 0.0f;
	for (int i = 0; i < 100; i++)
	{
		CurrentCheck_.push_back(false);
	}

	Timer_.push_back(0);
	Timer_.push_back(1);
	Timer_.push_back(1);
	Timer_.push_back(1);
	Timer_.push_back(1);
	Timer_.push_back(1);
	Timer_.push_back(1);
	Timer_.push_back(1);
	Timer_.push_back(1);
	Timer_.push_back(1);
	Timer_.push_back(1);
	Timer_.push_back(1);
	Timer_.push_back(1);
	Timer_.push_back(1);
}

void IntroManager::Update()
{
	CurrentTime_ += GameEngineTime::GetDeltaTime();

	if (true == IsStart(0))
	{
		CurrentCheck_[0] = true;
		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
		renderer->CreateAnimation("intro01_1.bmp", "intro01_1", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("intro01_1");
		renderer->Death(1);
	}

	if (true == IsStart(1))
	{
		CurrentCheck_[1] = true;
		GameEngineRenderer* renderer = CreateRenderer("intro01_2.bmp", RenderPivot::CENTER, { -170, -20 });
		renderer->Death(Timer_[2]);
	}
}

float IntroManager::CurrentTimer(int _Index)
{
	if (_Index >= Timer_.size())
	{
		return -1;
	}

	float ReturnF = 0.0f;
	for (int i = 0; i <= _Index; i++)
	{
		ReturnF += Timer_[i];
	}
	
	return ReturnF;
}

bool IntroManager::IsStart(int _Index)
{
	return CurrentTime_ >= CurrentTimer(_Index) && false == CurrentCheck_[_Index];
}

