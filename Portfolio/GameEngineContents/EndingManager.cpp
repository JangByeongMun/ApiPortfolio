#include "EndingManager.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngine.h>
#include "ContentsGlobal.h"

EndingManager::EndingManager()
	: CurrentTime_()
	, CurrentCheck_()
	, Timer_()
	, BgmPlayer_()
	, AnimationRenderer_()
	, AnimationStartTime_()
	, IsPlaying_()
{
}
EndingManager::~EndingManager() 
{
}

void EndingManager::Play()
{
	Reset();
	IsPlaying_ = true;

	BgmPlayer_ = GameEngineSound::SoundPlayControl("Ending.ogg");
	BgmPlayer_.SetVolume(0.02f * Option_MUSIC);
}

void EndingManager::Stop()
{
	Reset();
	IsPlaying_ = false;
	BgmPlayer_.Stop();
}

void EndingManager::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
	CurrentTime_ = 0;

	for (int i = 0; i <= 15; i++)
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
	Timer_.push_back(1.5f);			// 10
	Timer_.push_back(2);			// 11
	Timer_.push_back(1.2f);			// 12
	Timer_.push_back(1);			// 13
	Timer_.push_back(1);			// 14
	Timer_.push_back(8);			// 15
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
			AnimationRenderer_->CreateAnimation("None.bmp", "None", 0, 0, 0.1f, true);
			AnimationRenderer_->ChangeAnimation("epilogue11_2");
		}
	}
	else if (true == IsUpdate(10))
	{
		if (CurrentTime_ - AnimationStartTime_ >= 1.75f && CurrentTime_ - AnimationStartTime_ <= 1.8f)
		{
			AnimationRenderer_->ChangeAnimation("None");
		}
		else if (CurrentTime_ - AnimationStartTime_ >= 1.7f)
		{
			AnimationRenderer_->SetPivot(float4::Lerp(float4(-130, -80), float4(-260, -30), (CurrentTime_ - AnimationStartTime_ - 0.5f) * 4));
		}
		else if (CurrentTime_ - AnimationStartTime_ >= 0.5f)
		{
			AnimationRenderer_->SetPivot({ -130, -80 });
			AnimationRenderer_->ChangeAnimation("epilogue11_3");
		}
	}

	if (true == IsStart(11))
	{
		AnimationRenderer_->Death();
		CurrentCheck_[11] = true;

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 40 });
			renderer->CreateAnimation("epilogue12_1.bmp", "epilogue12_1", 0, 1, 0.1f, true);
			renderer->ChangeAnimation("epilogue12_1");
			renderer->Death(Timer_[12]);
		}

		{
			AnimationStartTime_ = CurrentTime_;

			AnimationRenderer_ = CreateRenderer(RenderPivot::CENTER, { -20, -270 });
			AnimationRenderer_->CreateAnimation("epilogue12_2.bmp", "epilogue12_2", 0, 1, 0.1f, true);
			AnimationRenderer_->ChangeAnimation("epilogue12_2");
		}
	}
	else if (true == IsUpdate(11))
	{
		if ((CurrentTime_ - AnimationStartTime_) >= 1)
		{
			AnimationRenderer_->SetPivot(float4::Lerp(float4(-20, -270), float4(-20, -220), (CurrentTime_ - AnimationStartTime_) * 5));
		}
	}

	if (true == IsStart(12))
	{
		AnimationRenderer_->Death();
		CurrentCheck_[12] = true;

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -30, 50 });
			renderer->CreateAnimation("epilogue13_1.bmp", "epilogue13_1", 0, 1, 0.1f, true);
			renderer->ChangeAnimation("epilogue13_1");
			renderer->Death(Timer_[13]);
		}

		{
			AnimationStartTime_ = CurrentTime_;

			AnimationRenderer_ = CreateRenderer(RenderPivot::CENTER, { -130, -160 });
			AnimationRenderer_->CreateAnimation("epilogue13_2.bmp", "epilogue13_2", 0, 1, 0.3f, false);
			AnimationRenderer_->CreateAnimation("None.bmp", "None", 0, 0, 0.1f, false);
			AnimationRenderer_->ChangeAnimation("epilogue13_2");
		}
	}
	else if (true == IsUpdate(12))
	{
		if (CurrentTime_ - AnimationStartTime_ >= 0.55f && CurrentTime_ - AnimationStartTime_ <= 0.6f)
		{
			AnimationRenderer_->ChangeAnimation("None");
		}
		else if ((CurrentTime_ - AnimationStartTime_) >= 0.3f)
		{
			AnimationRenderer_->SetPivot(float4::Lerp(float4(-130, -160), float4(-330, -360), (CurrentTime_ - AnimationStartTime_ - 0.3f) * 5));
		}
	}


	if (true == IsStart(13))
	{
		AnimationRenderer_->Death();
		CurrentCheck_[13] = true;

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -30, 135 });
			renderer->CreateAnimation("epilogue14_1.bmp", "epilogue14_1", 0, 1, 0.1f, true);
			renderer->ChangeAnimation("epilogue14_1");
			renderer->Death(Timer_[14]);
		}
	}

	if (true == IsStart(14))
	{
		CurrentCheck_[14] = true;

		{
			GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -20, 150 });
			renderer->CreateAnimation("epilogue15_1.bmp", "epilogue15_1", 0, 1, 0.1f, true);
			renderer->ChangeAnimation("epilogue15_1");
		}

		{
			AnimationStartTime_ = CurrentTime_;

			AnimationRenderer_ = CreateRenderer(RenderPivot::CENTER, { -230, 50 });
			AnimationRenderer_->CreateAnimation("epilogue15_2.bmp", "epilogue15_2", 0, 1, 0.1f, true);
			AnimationRenderer_->CreateAnimation("epilogue15_3.bmp", "epilogue15_3", 0, 1, 0.1f, true);
			AnimationRenderer_->ChangeAnimation("epilogue15_2");
		}
	}
	else if (true == IsUpdate(14))
	{
		if ((CurrentTime_ - AnimationStartTime_) >= 3.0f)
		{
			CreateRenderer("epilogue15_4.bmp", RenderPivot::CENTER, { -40, 120 });
		}
		else if ((CurrentTime_ - AnimationStartTime_) >= 2.5f)
		{
			AnimationRenderer_->SetPivot(float4::Lerp(float4(-230, 50), float4(-50, -20), (CurrentTime_ - AnimationStartTime_ - 2.5f) * 7));
			AnimationRenderer_->ChangeAnimation("epilogue15_3");
		}
	}

	if (true == IsStart(15))
	{
		CurrentCheck_[15] = true;
		BgmPlayer_.Stop();
		Reset();
		GameEngine::GetInst().ChangeLevel("Menu");
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
	return CurrentTime_ >= CurrentTimer(_Index) && false == CurrentCheck_[_Index] && true == IsPlaying_;
}
bool EndingManager::IsUpdate(int _Index)
{
	return CurrentTime_ >= CurrentTimer(_Index) && true == CurrentCheck_[_Index] && false == CurrentCheck_[_Index + 1] && true == IsPlaying_;
}
void EndingManager::Reset()
{
	CurrentTime_ = 0.0f;

	for (int i = 0; i < CurrentCheck_.size(); i++)
	{
		CurrentCheck_[i] = false;
	}

	AnimationRenderer_ = nullptr;
	AnimationStartTime_ = 0.0f;
	IsPlaying_ = false;
}