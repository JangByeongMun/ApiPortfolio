#include "EndingManager2.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

EndingManager2::EndingManager2() 
{
}

EndingManager2::~EndingManager2() 
{
}

void EndingManager2::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
	//CurrentTime_ = 0;
	CurrentState_ = EndingState::None;

	Timer_.push_back(0);			// 0
	Timer_.push_back(2.5f);			// 1
	Timer_.push_back(4);			// 2
	Timer_.push_back(2.5f);			// 3
	Timer_.push_back(3);			// 4
	Timer_.push_back(2.2f);			// 5
	Timer_.push_back(3);			// 6
	Timer_.push_back(3.5f);			// 7
	Timer_.push_back(2);			// 8
	Timer_.push_back(3);			// 9
	Timer_.push_back(1);			// 10
	Timer_.push_back(1);			// 11
	Timer_.push_back(1);			// 12
	Timer_.push_back(1);			// 13
	Timer_.push_back(1);			// 14

	ChangeState(EndingState::Ending1);
}

void EndingManager2::Update()
{
	switch (CurrentState_)
	{
	case EndingState::Ending1:
		Ending1Update();
		break;
	case EndingState::Ending2:
		Ending2Update();
		break;
	case EndingState::Ending3:
		Ending3Update();
		break;
	case EndingState::Ending4:
		Ending4Update();
		break;
	case EndingState::Ending5:
		Ending5Update();
		break;
	case EndingState::Ending6:
		Ending6Update();
		break;
	case EndingState::Ending7:
		Ending7Update();
		break;
	case EndingState::Ending8:
		Ending8Update();
		break;
	case EndingState::Ending9:
		Ending9Update();
		break;
	case EndingState::Ending10:
		Ending10Update();
		break;
	case EndingState::Ending11:
		Ending11Update();
		break;
	case EndingState::Ending12:
		Ending12Update();
		break;
	case EndingState::Ending13:
		Ending13Update();
		break;
	case EndingState::Ending14:
		Ending14Update();
		break;
	case EndingState::Ending15:
		Ending15Update();
		break;
	default:
		break;
	}
}

void EndingManager2::ChangeState(EndingState _State)
{
	if (CurrentState_ != _State)
	{
		switch (_State)
		{
		case EndingState::Ending1:
			Ending1Start();
			break;
		case EndingState::Ending2:
			Ending2Start();
			break;
		case EndingState::Ending3:
			Ending3Start();
			break;
		case EndingState::Ending4:
			Ending4Start();
			break;
		case EndingState::Ending5:
			Ending5Start();
			break;
		case EndingState::Ending6:
			Ending6Start();
			break;
		case EndingState::Ending7:
			Ending7Start();
			break;
		case EndingState::Ending8:
			Ending8Start();
			break;
		case EndingState::Ending9:
			Ending9Start();
			break;
		case EndingState::Ending10:
			Ending10Start();
			break;
		case EndingState::Ending11:
			Ending11Start();
			break;
		case EndingState::Ending12:
			Ending12Start();
			break;
		case EndingState::Ending13:
			Ending13Start();
			break;
		case EndingState::Ending14:
			Ending14Start();
			break;
		case EndingState::Ending15:
			Ending15Start();
			break;
		default:
			break;
		}
		
		AnimationStartTime_ = 0;
		CurrentState_ = _State;
	}
}

void EndingManager2::Ending1Start()
{
	CreateRenderer("epilogue01_1.bmp", RenderPivot::CENTER, { -20, -20 })->Death(Timer_[1]);

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 5, 15 });
	renderer->CreateAnimation("epilogue01_2.bmp", "epilogue01_2", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("epilogue01_2");
	renderer->Death(Timer_[1]);
}

void EndingManager2::Ending2Start()
{
	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -5, 0 });
	renderer->CreateAnimation("epilogue02_1.bmp", "epilogue02_1", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("epilogue02_1");
	renderer->Death(Timer_[2]);
}

void EndingManager2::Ending3Start()
{
		CreateRenderer("epilogue03_1.bmp", RenderPivot::CENTER, { 0, -10 })->Death(Timer_[3]);

		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 10, 15 });
		renderer->CreateAnimation("epilogue03_2.bmp", "epilogue03_2", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("epilogue03_2");
		renderer->Death(Timer_[3]);
}

void EndingManager2::Ending4Start()
{
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

void EndingManager2::Ending5Start()
{
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

void EndingManager2::Ending6Start()
{
	CreateRenderer("epilogue06_1.bmp", RenderPivot::CENTER, { -20, -105 })->Death(Timer_[6]);

}

void EndingManager2::Ending7Start()
{
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

void EndingManager2::Ending8Start()
{
	{
		CreateRenderer("epilogue08_1.bmp", RenderPivot::CENTER, { -40, 20 })->Death(Timer_[7]);
	}

	{
		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -30, 145 });
		renderer->CreateAnimation("epilogue08_2.bmp", "epilogue08_2", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("epilogue08_2");
		renderer->Death(Timer_[7]);
	}
}

void EndingManager2::Ending9Start()
{
	{
		CreateRenderer("epilogue09_1.bmp", RenderPivot::CENTER, { -50, 10 })->Death(Timer_[8]);
	}

	{
		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 20, 65 });
		renderer->CreateAnimation("epilogue09_2.bmp", "epilogue09_2", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("epilogue09_2");
		renderer->Death(Timer_[8]);
	}
}

void EndingManager2::Ending10Start()
{
	{
		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, -150 });
		renderer->CreateAnimation("epilogue10_1.bmp", "epilogue10_1", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("epilogue10_1");
		renderer->Death(Timer_[9]);
	}

	{
		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -30, 240 });
		renderer->CreateAnimation("epilogue10_2.bmp", "epilogue10_2", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("epilogue10_2");
		renderer->Death(Timer_[9]);
	}
}

void EndingManager2::Ending11Start()
{
	{
		CreateRenderer("epilogue11_1.bmp", RenderPivot::CENTER, { 20, 50 })->Death(Timer_[10]);
	}

	{
		AnimationRenderer_ = CreateRenderer(RenderPivot::CENTER, { -80, -25 });
		AnimationRenderer_->CreateAnimation("epilogue11_2.bmp", "epilogue11_2", 0, 1, 0.1f, true);
		AnimationRenderer_->CreateAnimation("epilogue11_3.bmp", "epilogue11_3", 0, 1, 0.1f, true);
		AnimationRenderer_->CreateAnimation("epilogue11_4.bmp", "epilogue11_4", 0, 0, 0.1f, true);
		AnimationRenderer_->ChangeAnimation("epilogue11_2");
		AnimationRenderer_->Death(Timer_[10]);
	}
}

void EndingManager2::Ending12Start()
{
}

void EndingManager2::Ending13Start()
{
}

void EndingManager2::Ending14Start()
{
}

void EndingManager2::Ending15Start()
{
}



////////////////////////////////////////////////// Update
void EndingManager2::Ending1Update()
{
	AnimationStartTime_ += GameEngineTime::GetDeltaTime();

	if (AnimationStartTime_ >= Timer_[0])
	{
	}
}

void EndingManager2::Ending2Update()
{
}

void EndingManager2::Ending3Update()
{
}

void EndingManager2::Ending4Update()
{
}

void EndingManager2::Ending5Update()
{
}

void EndingManager2::Ending6Update()
{
}

void EndingManager2::Ending7Update()
{
}

void EndingManager2::Ending8Update()
{
}

void EndingManager2::Ending9Update()
{
}

void EndingManager2::Ending10Update()
{
}

void EndingManager2::Ending11Update()
{
	AnimationStartTime_ += GameEngineTime::GetDeltaTime();

	if (AnimationStartTime_ >= 2)
	{
		AnimationRenderer_->ChangeAnimation("epilogue11_4");
	}
	else if (AnimationStartTime_ >= 1.95f)
	{
		AnimationRenderer_->SetPivot(float4(-130, -80) + float4(-3000, 1000) * (AnimationStartTime_ - 3));
	}
	else if (AnimationStartTime_ >= 0.95f)
	{
		AnimationRenderer_->SetPivot({ -130, -80 });
		AnimationRenderer_->ChangeAnimation("epilogue11_3");
	}
}

void EndingManager2::Ending12Update()
{
}

void EndingManager2::Ending13Update()
{
}

void EndingManager2::Ending14Update()
{
}

void EndingManager2::Ending15Update()
{
}
