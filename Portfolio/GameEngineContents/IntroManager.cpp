#include "IntroManager.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "Intro17.h"
#include "Intro18.h"
#include <GameEngine/GameEngine.h>

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

	for (int i = 0; i <= 28; i++)
	{
		CurrentCheck_.push_back(false);
	}

	Timer_.push_back(6.5f);			// 0
	Timer_.push_back(1.0f);			// 1
	Timer_.push_back(1.0f);			// 2
	Timer_.push_back(2.0f);			// 3
	Timer_.push_back(2.5f);			// 4
	Timer_.push_back(4.5f);			// 5
	Timer_.push_back(4.5f);			// 6
	Timer_.push_back(11.0f);		// 7
	Timer_.push_back(10.5f);		// 8
	Timer_.push_back(1.0f);			// 9
	Timer_.push_back(1.8f);			// 10
	Timer_.push_back(5.0f);			// 11
	Timer_.push_back(1.0f);			// 12
	Timer_.push_back(15.0f);		// 13
	Timer_.push_back(7.0f);			// 14
	Timer_.push_back(40.0f);		// 15
	Timer_.push_back(3.5f);			// 16
	Timer_.push_back(1.5f);			// 17
	Timer_.push_back(3.0f);			// 18
	Timer_.push_back(2.0f);			// 19
	Timer_.push_back(3.5f);			// 20
	Timer_.push_back(3.0f);			// 21
	Timer_.push_back(2.0f);			// 22
	Timer_.push_back(2.0f);			// 23
	Timer_.push_back(1.5f);			// 24
	Timer_.push_back(3.5f);			// 25
	Timer_.push_back(3.0f);			// 26
	Timer_.push_back(5.0f);			// 27
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

			AnimationRenderer2_->SetPivot({ 0, 150 });
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

	if (true == IsStart(12))
	{
		CurrentCheck_[12] = true;

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -20, 20 });
			renderer->CreateAnimation("Intro06_1.bmp", "Intro06_1", 0, 1, 0.4f, true);
			renderer->ChangeAnimation("Intro06_1");
			renderer->Death(Timer_[13]);
		}

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -30, -230 });
			renderer->CreateAnimation("Intro06_2.bmp", "Intro06_2", 0, 1, 0.2f, true);
			renderer->ChangeAnimation("Intro06_2");
			renderer->Death(Timer_[13]);
		}

		AnimationStartTime_ = CurrentTime_;
		AnimationRenderer1_ = CreateRenderer(RenderPivot::CENTER, { 30, -40 });
		AnimationRenderer1_->CreateAnimation("intro06_3.bmp", "Intro06_3_1", 0, 0, 0.2f, false);
		AnimationRenderer1_->CreateAnimation("intro06_3.bmp", "Intro06_3_2", 0, 1, 0.2f, true);
		AnimationRenderer1_->ChangeAnimation("Intro06_3_1");
	}
	else if (true == IsUpdate(12))
	{
		if (CurrentTime_ - AnimationStartTime_ >= 14.5f)
		{
			AnimationRenderer1_->ChangeAnimation("Intro06_3_1");
		}
		else if (CurrentTime_ - AnimationStartTime_ >= 10.5f)
		{
			AnimationRenderer1_->ChangeAnimation("Intro06_3_2");
		}
	}

	if (true == IsStart(13))
	{
		CurrentCheck_[13] = true;
		AnimationRenderer1_->Death();

		AnimationStartTime_ = CurrentTime_;
		AnimationRenderer1_ = CreateRenderer(RenderPivot::CENTER, { -30, -30 });
		AnimationRenderer1_->CreateAnimation("Intro12_1.bmp", "Intro12_1_1", 0, 0, 0.1f, true);
		AnimationRenderer1_->CreateAnimation("Intro12_1.bmp", "Intro12_1_2", 1, 1, 0.1f, true);
		AnimationRenderer1_->ChangeAnimation("Intro12_1_2");

		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 160, 220 });
		renderer->CreateAnimation("Intro12_2.bmp", "Intro12_2", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("Intro12_2");
		renderer->Death(Timer_[14]);
	}
	else if (true == IsUpdate(13))
	{
		if (CurrentTime_ - AnimationStartTime_ >= 2)
		{
			AnimationRenderer1_->ChangeAnimation("Intro12_1_1");
		}
	}
	
	if (true == IsStart(14))
	{
		CurrentCheck_[14] = true;
		AnimationRenderer1_->Death();

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -20, 20 });
			renderer->CreateAnimation("Intro06_1.bmp", "Intro06_1", 0, 1, 0.4f, true);
			renderer->ChangeAnimation("Intro06_1");
			renderer->Death(Timer_[15]);
		}

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -30, -230 });
			renderer->CreateAnimation("Intro06_2.bmp", "Intro06_2", 0, 1, 0.2f, true);
			renderer->ChangeAnimation("Intro06_2");
			renderer->Death(Timer_[15]);
		}

		AnimationStartTime_ = CurrentTime_;
		AnimationRenderer1_ = CreateRenderer(RenderPivot::CENTER, { 30, -40 });
		AnimationRenderer1_->CreateAnimation("Intro13_1.bmp", "Intro13_1_1", 1, 1, 0.2f, false);
		AnimationRenderer1_->CreateAnimation("Intro13_1.bmp", "Intro13_1_2", 0, 1, 0.4f, true);
		AnimationRenderer1_->ChangeAnimation("Intro13_1_1");
	}
	else if (true == IsUpdate(14))
	{
		if (CurrentTime_ - AnimationStartTime_ >= 16.5f)
		{
			AnimationRenderer1_->ChangeAnimation("Intro13_1_2");
		}
	}

	if (true == IsStart(15))
	{
		CurrentCheck_[15] = true;
		AnimationRenderer1_->Death();

		AnimationStartTime_ = CurrentTime_;
		AnimationRenderer1_ = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
		AnimationRenderer1_->CreateAnimation("Intro14_1.bmp", "Intro14_1_1", 0, 1, 0.1f, true);
		AnimationRenderer1_->CreateAnimation("Intro14_1.bmp", "Intro14_1_2", 2, 3, 0.1f, true);
		AnimationRenderer1_->CreateAnimation("Intro14_1.bmp", "Intro14_1_3", 4, 5, 0.1f, true);
		AnimationRenderer1_->ChangeAnimation("Intro14_1_1");
	}
	else if (true == IsUpdate(15))
	{ 
		if (CurrentTime_ - AnimationStartTime_ >= 3.0f && CurrentTime_ - AnimationStartTime_ <= 3.5f)
		{
			AnimationRenderer1_->ChangeAnimation("Intro14_1_3");
		}
		else if (CurrentTime_ - AnimationStartTime_ >= 1.5f)
		{
			AnimationRenderer1_->ChangeAnimation("Intro14_1_2");
		}
	}

	if (true == IsStart(16))
	{
		CurrentCheck_[16] = true;
		AnimationRenderer1_->Death();

		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
		renderer->CreateAnimation("Intro15_1.bmp", "Intro15_1", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("Intro15_1");
		renderer->Death(Timer_[17]);
	}

	if (true == IsStart(17))
	{
		CurrentCheck_[17] = true;

		CreateRenderer("Intro16_1.bmp", RenderPivot::CENTER, { 0, 0 })->Death(Timer_[18]);

		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
		renderer->CreateAnimation("Intro16_2.bmp", "Intro16_2", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("Intro16_2");
		renderer->Death(Timer_[18]);
	}

	if (true == IsStart(18))
	{
		CurrentCheck_[18] = true;

		GetLevel()->CreateActor<Intro17>()->Death(Timer_[19]);
	}

	if (true == IsStart(19))
	{
		CurrentCheck_[19] = true;

		GetLevel()->CreateActor<Intro18>()->Death(Timer_[20]);
	}

	if (true == IsStart(20))
	{
		CurrentCheck_[20] = true;

		CreateRenderer("Intro19_1.bmp", RenderPivot::CENTER, { 0, 70 })->Death(Timer_[21]);

		AnimationStartTime_ = CurrentTime_;
		AnimationRenderer1_ = CreateRenderer(RenderPivot::CENTER, { -160, -30 });
		AnimationRenderer1_->CreateAnimation("Intro19_2.bmp", "Intro19_2", 0, 1, 0.1f, true);
		AnimationRenderer1_->CreateAnimation("Intro19_3.bmp", "Intro19_3", 0, 1, 0.1f, true);
		AnimationRenderer1_->ChangeAnimation("Intro19_2");
	}
	else if (true == IsUpdate(20))
	{
		if (CurrentTime_ - AnimationStartTime_ >= 2 && CurrentTime_ - AnimationStartTime_ <= 2.5f)
		{
			AnimationRenderer1_->ChangeAnimation("Intro19_3");
			AnimationRenderer1_->SetPivot({ -180, -30 });
		}
	}

	if (true == IsStart(21))
	{
		CurrentCheck_[21] = true;
		AnimationRenderer1_->Death();

		AnimationStartTime_ = CurrentTime_;
		AnimationRenderer1_ = CreateRenderer(RenderPivot::CENTER, { 0, 0 });
		AnimationRenderer1_->CreateAnimation("Intro20_1.bmp", "Intro20_1_1", 0, 0, 0.1f, false);
		AnimationRenderer1_->CreateAnimation("Intro20_1.bmp", "Intro20_1_2", 1, 1, 0.1f, false);
		AnimationRenderer1_->ChangeAnimation("Intro20_1_1");
	}
	else if (true == IsUpdate(21))
	{
		if (CurrentTime_ - AnimationStartTime_ >= 1.5f)
		{
			CreateRenderer("Intro20_2.bmp", RenderPivot::CENTER, { -10, -180 })->Death(0.1f);
		}
		else if (CurrentTime_ - AnimationStartTime_ >= 1.0f)
		{
			AnimationRenderer1_->ChangeAnimation("Intro20_1_2");
		}
	}

	if (true == IsStart(22))
	{
		CurrentCheck_[22] = true;
		AnimationRenderer1_->Death();

		CreateRenderer("Intro21_1.bmp", RenderPivot::CENTER, { 20, 130 })->Death(Timer_[23]);

		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -90, 40 });
		renderer->CreateAnimation("intro21_2.bmp", "intro21_2", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("intro21_2");
		renderer->Death(Timer_[23]);
	}

	if (true == IsStart(23))
	{
		CurrentCheck_[23] = true;

		AnimationStartTime_ = CurrentTime_;
		AnimationRenderer1_ = CreateRenderer("intro22_1.bmp", RenderPivot::CENTER, { -20, 80 });

		AnimationRenderer2_ = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
		AnimationRenderer2_->CreateAnimation("Intro22_2.bmp", "Intro22_2", 0, 1, 0.1f, true);
		AnimationRenderer2_->CreateAnimation("Intro22_4.bmp", "Intro22_4", 0, 1, 0.1f, true);
		AnimationRenderer2_->CreateAnimation("None.bmp", "None", 0, 0, 0.1f, false);
		AnimationRenderer2_->ChangeAnimation("None");
	}
	else if (true == IsUpdate(23))
	{
		if (CurrentTime_ - AnimationStartTime_ >= 1.0f && CurrentTime_ - AnimationStartTime_ <= 1.5f)
		{
			AnimationRenderer2_->ChangeAnimation("Intro22_4");
		}
		else if (CurrentTime_ - AnimationStartTime_ >= 0.5f)
		{
			AnimationRenderer1_->SetImage("intro22_3.bmp");
			AnimationRenderer1_->SetPivot({ 150, 120 });

			AnimationRenderer2_->ChangeAnimation("Intro22_2");
			AnimationRenderer2_->SetPivot({ -150, 50 });
		}
	}

	if (true == IsStart(24))
	{
		CurrentCheck_[24] = true;
		AnimationRenderer1_->Death();
		AnimationRenderer2_->Death();

		AnimationStartTime_ = CurrentTime_;
		AnimationRenderer1_ = CreateRenderer("Intro23_1.bmp", RenderPivot::CENTER, { -20, -100 });

		AnimationRenderer2_ = CreateRenderer(RenderPivot::CENTER, { 40, 190 });
		AnimationRenderer2_->CreateAnimation("Intro23_3.bmp", "Intro23_3", 0, 1, 0.1f, true);
		AnimationRenderer2_->CreateAnimation("Intro23_4.bmp", "Intro23_4", 0, 1, 0.1f, true);
		AnimationRenderer2_->ChangeAnimation("Intro23_3");
	}
	else if (true == IsUpdate(24))
	{
		if (CurrentTime_ - AnimationStartTime_ >= 2 && CurrentTime_ - AnimationStartTime_ <= 2.5f)
		{
			AnimationRenderer1_->SetImage("Intro23_2.bmp");
			AnimationRenderer1_->SetPivot({ 20, -110 });

			AnimationRenderer2_->ChangeAnimation("Intro23_4");
			AnimationRenderer2_->SetPivot({ -35, 40 });
		}
	}

	if (true == IsStart(25))
	{
		CurrentCheck_[25] = true;
		AnimationRenderer1_->Death();
		AnimationRenderer2_->Death();

		AnimationStartTime_ = CurrentTime_;
		AnimationRenderer1_ = CreateRenderer("Intro24_1.bmp", RenderPivot::CENTER, { 90, 120 });

		AnimationRenderer2_ = CreateRenderer(RenderPivot::CENTER, { -150, 20 });
		AnimationRenderer2_->CreateAnimation("Intro24_2.bmp", "Intro24_2", 0, 1, 0.1f, true);
		AnimationRenderer2_->CreateAnimation("Intro24_3.bmp", "Intro24_3", 0, 0, 0.1f, false);
		AnimationRenderer2_->CreateAnimation("None.bmp", "None", 0, 0, 0.1f, false);
		AnimationRenderer2_->ChangeAnimation("Intro24_2");
	}
	else if (true == IsUpdate(25))
	{
		if (CurrentTime_ - AnimationStartTime_ >= 2.4f)
		{
			AnimationRenderer1_->SetImage("Intro24_1.bmp");
		}
		else if (CurrentTime_ - AnimationStartTime_ >= 2.2f)
		{
			AnimationRenderer2_->ChangeAnimation("None");
			AnimationRenderer1_->SetImage("Intro24_4.bmp");
		}
		else if (CurrentTime_ - AnimationStartTime_ >= 2)
		{
			AnimationRenderer2_->ChangeAnimation("Intro24_3");
			AnimationRenderer2_->SetPivot({ -50, -20 });
		}
	}

	if (true == IsStart(26))
	{
		CurrentCheck_[26] = true;
		AnimationRenderer1_->Death();
		AnimationRenderer2_->Death();

		CreateRenderer("Intro25_2.bmp", RenderPivot::CENTER, { -20, 100 })->Death(Timer_[27]);

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -20, 50 });
			renderer->CreateAnimation("Intro25_1.bmp", "Intro25_1", 0, 1, 0.1f, true);
			renderer->ChangeAnimation("Intro25_1");
		}

		AnimationStartTime_ = CurrentTime_;
		AnimationRenderer1_ = CreateRenderer(RenderPivot::CENTER, { -40, 90 });
		AnimationRenderer1_->CreateAnimation("Intro25_3.bmp", "Intro25_3", 0, 0, 0.1f, false);
		AnimationRenderer1_->CreateAnimation("Intro25_4.bmp", "Intro25_4", 0, 1, 0.1f, true);
		AnimationRenderer1_->ChangeAnimation("Intro25_3");
	}
	else if (true == IsUpdate(26))
	{
		if (CurrentTime_ - AnimationStartTime_ <= 0.2f)
		{
			AnimationRenderer1_->SetPivot(float4::Lerp({ -40, 90 }, { -40, 130 }, (CurrentTime_ - AnimationStartTime_) * 5));
		}

		if (CurrentTime_ - AnimationStartTime_ >= 0.2f && CurrentTime_ - AnimationStartTime_ <= 0.25f)
		{
			AnimationRenderer1_->ChangeAnimation("Intro25_4");
		}
	}

	if (true == IsStart(27))
	{
		CurrentCheck_[27] = true;
		AnimationRenderer1_->Death();
		AnimationRenderer2_->Death();

		BgmPlayer_.Stop();
		Reset();
		GameEngine::GetInst().ChangeLevel("Menu");
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