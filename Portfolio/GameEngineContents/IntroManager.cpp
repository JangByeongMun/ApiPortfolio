#include "IntroManager.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

IntroManager::IntroManager() 
	: CurrentTime_(0)
	, CurrentCheck_({})
	, Timer_({})
	, BgmPlayer_()
	, AnimationRenderer1_(nullptr)
	, AnimationRenderer2_(nullptr)
	, AnimationStartTime_(0)
	, IsPlaying_(true)
{
}

IntroManager::~IntroManager() 
{
}

void IntroManager::Play()
{
	Reset();
	IsPlaying_ = true;

	BgmPlayer_ = GameEngineSound::SoundPlayControl("Intro.ogg");
	BgmPlayer_.SetVolume(0.1f);
}

void IntroManager::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
	CurrentTime_ = 0.0f;

	for (int i = 0; i <= 25; i++)
	{
		CurrentCheck_.push_back(false);
	}

	Timer_.push_back(6.5f);			// 0
	Timer_.push_back(1);			// 1
	Timer_.push_back(1);			// 2
	Timer_.push_back(2.0f);			// 3
	Timer_.push_back(2.5f);			// 4
	Timer_.push_back(4.5f);			// 5
	Timer_.push_back(4.5f);			// 6
	Timer_.push_back(11);			// 7
	Timer_.push_back(10.5f);		// 8
	Timer_.push_back(1);			// 9
	Timer_.push_back(1.8f);			// 10
	Timer_.push_back(5.0f);			// 11
	Timer_.push_back(100);			// 12
	Timer_.push_back(100);			// 13
	Timer_.push_back(100);			// 14
	Timer_.push_back(100);			// 15
	Timer_.push_back(100);			// 16
	Timer_.push_back(100);			// 17
	Timer_.push_back(100);			// 18
	Timer_.push_back(100);			// 19
	Timer_.push_back(100);			// 20
	Timer_.push_back(100);			// 21
	Timer_.push_back(100);			// 22
	Timer_.push_back(100);			// 23
	Timer_.push_back(100);			// 24
	Timer_.push_back(100);			// 25
}


void IntroManager::Update()
{
	CurrentTime_ += GameEngineTime::GetDeltaTime();

	if (true == IsStart(0))
	{
		CurrentCheck_[0] = true;

		AnimationStartTime_ = CurrentTime_;

		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
		renderer->CreateAnimation("intro01_1.bmp", "intro01_1", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("intro01_1");
		renderer->Death(Timer_[1]+ Timer_[2] + Timer_[3]);
	}

	if (true == IsStart(1))
	{
		CurrentCheck_[1] = true;
		GameEngineRenderer* renderer = CreateRenderer("intro01_2.bmp", RenderPivot::CENTER, { -170, -20 });
		renderer->Death(Timer_[2] + Timer_[3]);
	}

	if (true == IsStart(2))
	{
		CurrentCheck_[2] = true;
		GameEngineRenderer* renderer = CreateRenderer("intro01_3.bmp", RenderPivot::CENTER, { 200, -90 });
		renderer->Death(Timer_[3]);
	}

	if (true == IsStart(3))
	{
		CurrentCheck_[3] = true;
		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
		renderer->CreateAnimation("intro02_1.bmp", "intro02_1", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("intro02_1");
		renderer->Death(Timer_[4]);
	}

	if (true == IsStart(4))
	{
		CurrentCheck_[4] = true;
		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
		renderer->CreateAnimation("Intro03_1.bmp", "Intro03_1", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("Intro03_1");
		renderer->Death(Timer_[5]);
	}

	if (true == IsStart(5))
	{
		CurrentCheck_[5] = true;
		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -30, 50 });
		renderer->CreateAnimation("Intro04_1.bmp", "Intro04_1", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("Intro04_1");
		renderer->Death(Timer_[6]);
	}

	if (true == IsStart(6))
	{
		CurrentCheck_[6] = true;

		CreateRenderer("intro05_1.bmp", RenderPivot::CENTER, { 0, 0 })->Death(Timer_[7]);
		CreateRenderer("intro05_4.bmp", RenderPivot::CENTER, { 160, 280 })->Death(Timer_[7]);

		AnimationStartTime_ = CurrentTime_;
		AnimationRenderer1_ = CreateRenderer(RenderPivot::CENTER, { -20, 0 });
		AnimationRenderer1_->CreateAnimation("Intro05_2.bmp", "Intro05_2", 0, 1, 0.1f, true);
		AnimationRenderer1_->CreateAnimation("Intro05_5.bmp", "Intro05_5", 0, 1, 0.1f, true);
		AnimationRenderer1_->ChangeAnimation("Intro05_2");

		AnimationRenderer2_ = CreateRenderer(RenderPivot::CENTER, { 190, 170 });
		AnimationRenderer2_->CreateAnimation("Intro05_3.bmp", "Intro05_3", 0, 1, 0.1f, true);
		AnimationRenderer2_->CreateAnimation("Intro05_6.bmp", "Intro05_6", 0, 0, 0.1f, true);
		AnimationRenderer2_->ChangeAnimation("Intro05_3");
	}
	else if (true == IsUpdate(6))
	{
		if (CurrentTime_ - AnimationStartTime_ >= 9)
		{
			AnimationRenderer1_->SetPivot({ -25, 5 });
			AnimationRenderer1_->ChangeAnimation("Intro05_5");
		}

		if (CurrentTime_ - AnimationStartTime_ >= 10)
		{
			AnimationRenderer2_->ChangeAnimation("Intro05_6");
		}
	}

	if (true == IsStart(7))
	{
		CurrentCheck_[7] = true;
		AnimationRenderer1_->Death();
		AnimationRenderer2_->Death();

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -20, 20 });
			renderer->CreateAnimation("Intro06_1.bmp", "Intro06_1", 0, 1, 0.4f, true);
			renderer->ChangeAnimation("Intro06_1");
			renderer->Death(Timer_[8]);
		}

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -30, -230 });
			renderer->CreateAnimation("Intro06_2.bmp", "Intro06_2", 0, 1, 0.2f, true);
			renderer->ChangeAnimation("Intro06_2");
			renderer->Death(Timer_[8]);
		}

		AnimationStartTime_ = CurrentTime_;
		AnimationRenderer1_ = CreateRenderer(RenderPivot::CENTER, { 30, -40 });
		AnimationRenderer1_->CreateAnimation("Intro06_3.bmp", "Intro06_3_1", 0, 0, 0.2f, false);
		AnimationRenderer1_->CreateAnimation("Intro06_3.bmp", "Intro06_3_2", 0, 1, 0.2f, true);
		AnimationRenderer1_->ChangeAnimation("Intro06_3_1");
	}
	else if (true == IsUpdate(7))
	{
		if (CurrentTime_ - AnimationStartTime_ >= 10)
		{
			AnimationRenderer1_->ChangeAnimation("Intro06_3_1");
		}
		else if (CurrentTime_ - AnimationStartTime_ >= 7)
		{
			AnimationRenderer1_->ChangeAnimation("Intro06_3_2");
		}
	}

	if (true == IsStart(8))
	{
		CurrentCheck_[8] = true;
		AnimationRenderer1_->Death();

		CreateRenderer("intro05_1.bmp", RenderPivot::CENTER, { 0, 0 })->Death(Timer_[9]);
		CreateRenderer("intro05_4.bmp", RenderPivot::CENTER, { 160, 280 })->Death(Timer_[9]);

		CreateRenderer("intro07_1.bmp", RenderPivot::CENTER, { -20, 50 })->Death(Timer_[9]);

		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 190, 170 });
		renderer->CreateAnimation("Intro07_2.bmp", "Intro07_2", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("Intro07_2");
		renderer->Death(Timer_[9]);
	}

	if (true == IsStart(9))
	{
		CurrentCheck_[9] = true;

		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
		renderer->CreateAnimation("Intro08_1.bmp", "Intro08_1", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("Intro08_1");
		renderer->Death(Timer_[10]);
	}
	
	if (true == IsStart(10))
	{
		CurrentCheck_[10] = true;

		AnimationStartTime_ = CurrentTime_;
		AnimationRenderer1_ = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
		AnimationRenderer1_->CreateAnimation("Intro09_1.bmp", "Intro09_1", 0, 1, 0.1f, true);
		AnimationRenderer1_->CreateAnimation("Intro09_2.bmp", "Intro09_2", 0, 1, 0.1f, true);
		AnimationRenderer1_->CreateAnimation("Intro09_3.bmp", "Intro09_3", 0, 1, 0.1f, true);
		AnimationRenderer1_->CreateAnimation("Intro09_4.bmp", "Intro09_4", 0, 1, 0.1f, true);
		AnimationRenderer1_->CreateAnimation("Intro09_5.bmp", "Intro09_5", 0, 1, 0.1f, true);
		AnimationRenderer1_->ChangeAnimation("Intro09_1");

		AnimationRenderer2_ = CreateRenderer(RenderPivot::CENTER, { 150, 0 });
		AnimationRenderer2_->CreateAnimation("intro09_6.bmp", "intro09_6", 0, 3, 0.1f, false);
		AnimationRenderer2_->CreateAnimation("intro09_7.bmp", "intro09_7", 0, 3, 0.1f, false);
		AnimationRenderer2_->CreateAnimation("intro09_8.bmp", "intro09_8", 0, 3, 0.1f, false);
		AnimationRenderer2_->CreateAnimation("None.bmp", "None", 0, 0, 0.1f, false);
		AnimationRenderer2_->ChangeAnimation("None");

	}
	else if (true == IsUpdate(10))
	{
		if (CurrentTime_ - AnimationStartTime_ >= 4 && CurrentTime_ - AnimationStartTime_ <= 5)
		{
			AnimationRenderer1_->ChangeAnimation("Intro09_5");
			AnimationRenderer1_->SetPivot({ 0, 30 });
		}
		else if (CurrentTime_ - AnimationStartTime_ >= 3)
		{
			AnimationRenderer1_->ChangeAnimation("Intro09_4");
			AnimationRenderer1_->SetPivot({ -10, 0 });

			AnimationRenderer2_->SetPivot({ 0, 100 });
			AnimationRenderer2_->ChangeAnimation("intro09_8");
		}
		else if (CurrentTime_ - AnimationStartTime_ >= 2)
		{
			AnimationRenderer1_->ChangeAnimation("Intro09_3");
			AnimationRenderer1_->SetPivot({ -20, 20 });

			AnimationRenderer2_->SetPivot({ -150, 0 });
			AnimationRenderer2_->ChangeAnimation("intro09_7");
		}
		else if (CurrentTime_ - AnimationStartTime_ >= 1)
		{
			AnimationRenderer1_->ChangeAnimation("Intro09_2");
			AnimationRenderer1_->SetPivot({ -10, 20 });

			AnimationRenderer2_->SetPivot({ 150, 0 });
			AnimationRenderer2_->ChangeAnimation("intro09_6");
		}
	}

	if (true == IsStart(11))
	{
		CurrentCheck_[11] = true;
		AnimationRenderer1_->Death();
		AnimationRenderer2_->Death();

		CreateRenderer("intro05_1.bmp", RenderPivot::CENTER, { 0, 0 })->Death(Timer_[12]);

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -15, 10 });
			renderer->CreateAnimation("Intro10_1.bmp", "Intro10_1", 0, 1, 0.1f, true);
			renderer->ChangeAnimation("Intro10_1");
			renderer->Death(Timer_[12]);
		}

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 170, 220 });
			renderer->CreateAnimation("Intro10_2.bmp", "Intro10_2", 0, 1, 0.1f, true);
			renderer->ChangeAnimation("Intro10_2");
			renderer->Death(Timer_[12]);
		}
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
	return CurrentTime_ >= CurrentTimer(_Index) && false == CurrentCheck_[_Index] && true == IsPlaying_;
}
bool IntroManager::IsUpdate(int _Index)
{
	return CurrentTime_ >= CurrentTimer(_Index) && true == CurrentCheck_[_Index] && false == CurrentCheck_[_Index + 1] && true == IsPlaying_;
}
void IntroManager::Reset()
{
	CurrentTime_ = 0.0f;

	for (int i = 0; i < CurrentCheck_.size(); i++)
	{
		CurrentCheck_[i] = false;
	}

	AnimationRenderer1_ = nullptr;
	AnimationRenderer2_ = nullptr;
	AnimationStartTime_ = 0.0f;
	IsPlaying_ = false;
}