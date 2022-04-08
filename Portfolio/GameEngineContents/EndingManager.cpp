#include "EndingManager.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

EndingManager::EndingManager() 
	: CurrentTime_()
	, CurrentCheck_()
	, Timer_()
	, AnimationRenderer_()
	, AnimationStartTime_()
{
}

EndingManager::~EndingManager() 
{
}

void EndingManager::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CurrentTime_ = 0;

	for (int i = 0; i < 100; i++)
	{
		CurrentCheck_.push_back(false);
	}

	Timer_.push_back(0);			// 0
	Timer_.push_back(2.5f);			// 1
	Timer_.push_back(4);			// 2
	Timer_.push_back(2.5f);			// 3
	Timer_.push_back(3);			// 4
	Timer_.push_back(2.2f);			// 5
	Timer_.push_back(3);			// 6
	Timer_.push_back(3.5f);			// 7
	Timer_.push_back(3.2f);			// 8
	Timer_.push_back(3);			// 9
	Timer_.push_back(2.5f);			// 10
	Timer_.push_back(100);			// 11
	Timer_.push_back(100);			// 12
	Timer_.push_back(100);			// 13
}

void EndingManager::Update()
{
	CurrentTime_ += GameEngineTime::GetDeltaTime();

	if (true == IsStart(0))
	{
		CurrentCheck_[0] = true;
		{
			CreateRenderer("epilogue01_1.bmp", RenderPivot::CENTER, { -20, -20 })->Death(Timer_[1]);
		}

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 5, 15 });
			renderer->CreateAnimation("epilogue01_2.bmp", "epilogue01_2", 0, 1, 0.1f, true);
			renderer->ChangeAnimation("epilogue01_2");
			renderer->Death(Timer_[1]);
		}
	}

	if (true == IsStart(1))
	{
		CurrentCheck_[1] = true;

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -5, 0 });
			renderer->CreateAnimation("epilogue02_1.bmp", "epilogue02_1", 0, 1, 0.1f, true);
			renderer->ChangeAnimation("epilogue02_1");
			renderer->Death(Timer_[2]);
		}
	}

	if (true == IsStart(2))
	{
		CurrentCheck_[2] = true;

		{
			CreateRenderer("epilogue03_1.bmp", RenderPivot::CENTER, { 0, -10 })->Death(Timer_[3]);
		}

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 10, 15 });
			renderer->CreateAnimation("epilogue03_2.bmp", "epilogue03_2", 0, 1, 0.1f, true);
			renderer->ChangeAnimation("epilogue03_2");
			renderer->Death(Timer_[3]);
		}
	}

	if (true == IsStart(3))
	{
		CurrentCheck_[3] = true;

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
			renderer->CreateAnimation("epilogue04_1.bmp", "epilogue04_1", 0, 1, 0.1f, true);
			renderer->ChangeAnimation("epilogue04_1");
			renderer->Death(Timer_[4]);
		}

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 10, 80 });
			renderer->CreateAnimation("epilogue04_2.bmp", "epilogue04_2", 0, 1, 0.2f, true);
			renderer->ChangeAnimation("epilogue04_2");
			renderer->Death(Timer_[4]);
		}
	}

	if (true == IsStart(4))
	{
		CurrentCheck_[4] = true;

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -50, -40 });
			renderer->CreateAnimation("epilogue05_1.bmp", "epilogue05_1", 0, 1, 0.1f, true);
			renderer->ChangeAnimation("epilogue05_1");
			renderer->Death(Timer_[5] + Timer_[6]);
		}

		{   // 똑같은 입 사용하므로 4_2 재활용
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -20, -100 });
			renderer->CreateAnimation("epilogue04_2.bmp", "epilogue04_2", 0, 1, 0.2f, true);
			renderer->ChangeAnimation("epilogue04_2");
			renderer->Death(Timer_[5]);
		}
	}

	if (true == IsStart(5))
	{
		CurrentCheck_[5] = true;

		{
			CreateRenderer("epilogue06_1.bmp", RenderPivot::CENTER, { -20, -105 })->Death(Timer_[6]);
		}
	}

	if (true == IsStart(6))
	{
		CurrentCheck_[6] = true;

		{
			CreateRenderer("epilogue07_1.bmp", RenderPivot::CENTER, { -20, -20 })->Death(Timer_[7]);
		}

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 20, 100 });
			renderer->CreateAnimation("epilogue07_2.bmp", "epilogue07_2", 0, 1, 0.1f, true);
			renderer->ChangeAnimation("epilogue07_2");
			renderer->Death(Timer_[7]);
		}
	}

	if (true == IsStart(7))
	{
		CurrentCheck_[7] = true;

		{
			CreateRenderer("epilogue08_1.bmp", RenderPivot::CENTER, { -40, 20 })->Death(Timer_[8]);
		}

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -30, 145 });
			renderer->CreateAnimation("epilogue08_2.bmp", "epilogue08_2", 0, 1, 0.1f, true);
			renderer->ChangeAnimation("epilogue08_2");
			renderer->Death(Timer_[8]);
		}
	}

	if (true == IsStart(8))
	{
		CurrentCheck_[8] = true;

		{
			CreateRenderer("epilogue09_1.bmp", RenderPivot::CENTER, { -50, 10 })->Death(Timer_[9]);
		}

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 20, 65 });
			renderer->CreateAnimation("epilogue09_2.bmp", "epilogue09_2", 0, 1, 0.1f, true);
			renderer->ChangeAnimation("epilogue09_2");
			renderer->Death(Timer_[9]);
		}
	}

	if (true == IsStart(9))
	{
		CurrentCheck_[9] = true;
	
		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, -150 });
			renderer->CreateAnimation("epilogue10_1.bmp", "epilogue10_1", 0, 1, 0.1f, true);
			renderer->ChangeAnimation("epilogue10_1");
			renderer->Death(Timer_[10]);
		}
	
		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -30, 240 });
			renderer->CreateAnimation("epilogue10_2.bmp", "epilogue10_2", 0, 1, 0.1f, true);
			renderer->ChangeAnimation("epilogue10_2");
			renderer->Death(Timer_[10]);
		}
	}
	
	if (true == IsStart(10))
	{
		CurrentCheck_[10] = true;
	
		{
			CreateRenderer("epilogue11_1.bmp", RenderPivot::CENTER, { 20, 50 })->Death(Timer_[11]);
		}
	
		{
			AnimationStartTime_ = CurrentTime_;
	
			AnimationRenderer_ = CreateRenderer(RenderPivot::CENTER, { -80, -25 });
			AnimationRenderer_->CreateAnimation("epilogue11_2.bmp", "epilogue11_2", 0, 1, 0.1f, true);
			AnimationRenderer_->CreateAnimation("epilogue11_3.bmp", "epilogue11_3", 0, 1, 0.1f, true);
			AnimationRenderer_->CreateAnimation("epilogue11_4.bmp", "epilogue11_4", 0, 0, 0.1f, true);
			AnimationRenderer_->ChangeAnimation("epilogue11_2");
			AnimationRenderer_->Death(Timer_[11]);
		}
	}
	else if (true == IsUpdate(10))
	{
		if (CurrentTime_ - AnimationStartTime_ >= 2)
		{
			AnimationRenderer_->ChangeAnimation("epilogue11_4");
		}
		else if (CurrentTime_ - AnimationStartTime_ >= 1.95f)
		{
			AnimationRenderer_->SetPivot(float4(-130, -80) + float4(-3000, 1000) * (CurrentTime_ - AnimationStartTime_ - 0.95f));
		}
		else if (CurrentTime_ - AnimationStartTime_ >= 0.95f)
		{
			AnimationRenderer_->SetPivot({ -130, -80 });
			AnimationRenderer_->ChangeAnimation("epilogue11_3");
		}
	}
}

float EndingManager::CurrentTimer(int _Index)
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

bool EndingManager::IsStart(int _Index)
{
	return CurrentTime_ >= CurrentTimer(_Index) && false == CurrentCheck_[_Index];
}
bool EndingManager::IsUpdate(int _Index)
{
	return CurrentTime_ >= CurrentTimer(_Index) && true == CurrentCheck_[_Index] && false == CurrentCheck_[_Index + 1];
}