#include "PauseUI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Player.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>

PauseUI::PauseUI() 
	: IsPause_(false)
	, ArrowRenderer_(nullptr)
	, ArrowIndex_(0)
{
}

PauseUI::~PauseUI() 
{
}

void PauseUI::SettingValue()
{
	// 이동속도
	{
		float TmpValue = Player::MainPlayer->GetMoveSpeed();
		if (TmpValue < 1.00f)
		{
			RendererVector_[0]->SetIndex(6);
		}
		else if (1.00f <= TmpValue && TmpValue < 1.50f)
		{
			RendererVector_[0]->SetIndex(5);
		}
		else if (1.50f <= TmpValue && TmpValue < 2.00f)
		{
			RendererVector_[0]->SetIndex(4);
		}
		else if (2.00f <= TmpValue)
		{
			RendererVector_[0]->SetIndex(3);
		}
	}


	// 공격속도
	{
		float TmpValue = Player::MainPlayer->GetAttackSpeed();
		if (TmpValue < 1.00f)
		{
			RendererVector_[1]->SetIndex(13);
		}
		if (1.0f <= TmpValue && TmpValue < 2.0f)
		{
			RendererVector_[1]->SetIndex(12);
		}
		else if (2.0f <= TmpValue && TmpValue < 3.0f)
		{
			RendererVector_[1]->SetIndex(11);
		}
		else if (3.0f <= TmpValue && TmpValue < 4.0f)
		{
			RendererVector_[1]->SetIndex(10);
		}
		else if (4.0f <= TmpValue && TmpValue < 5.0f)
		{
			RendererVector_[1]->SetIndex(9);
		}
		else if (5.0f <= TmpValue && TmpValue < 6.0f)
		{
			RendererVector_[1]->SetIndex(8);
		}
		else if (6.0f <= TmpValue)
		{
			RendererVector_[1]->SetIndex(7);
		}
	}


	// 공격력
	{
		float TmpValue = Player::MainPlayer->GetDamage();
		if (TmpValue < 3.0f)
		{
			RendererVector_[2]->SetIndex(6);
		}
		else if (3.0f <= TmpValue && TmpValue < 4.5f)
		{
			RendererVector_[2]->SetIndex(5);
		}
		else if (4.5f <= TmpValue && TmpValue < 6.0f)
		{
			RendererVector_[2]->SetIndex(4);
		}
		else if (6.0f <= TmpValue && TmpValue < 7.5f)
		{
			RendererVector_[2]->SetIndex(3);
		}
		else if (7.5f <= TmpValue && TmpValue < 9.0f)
		{
			RendererVector_[2]->SetIndex(2);
		}
		else if (9.0f <= TmpValue && TmpValue < 10.5f)
		{
			RendererVector_[2]->SetIndex(1);
		}
		else if (10.5f <= TmpValue)
		{
			RendererVector_[2]->SetIndex(0);
		}
	}

	// 사거리
	{
		float TmpValue = Player::MainPlayer->GetRange();
		if (TmpValue < 5.0f)
		{
			RendererVector_[3]->SetIndex(13);
		}
		if (5.0f <= TmpValue && TmpValue < 6.5f)
		{
			RendererVector_[3]->SetIndex(12);
		}
		else if (6.5f <= TmpValue && TmpValue < 8.0f)
		{
			RendererVector_[3]->SetIndex(11);
		}
		else if (8.0f <= TmpValue && TmpValue < 9.5f)
		{
			RendererVector_[3]->SetIndex(10);
		}
		else if (9.5f <= TmpValue && TmpValue < 11.0f)
		{
			RendererVector_[3]->SetIndex(9);
		}
		else if (11.0f <= TmpValue && TmpValue < 12.5f)
		{
			RendererVector_[3]->SetIndex(8);
		}
		else if (12.5f <= TmpValue)
		{
			RendererVector_[3]->SetIndex(7);
		}
	}

	// 눈물속도
	{
		float TmpValue = Player::MainPlayer->GetShotSpeed();
		if (TmpValue < 1.0f)
		{
			RendererVector_[4]->SetIndex(6);
		}
		else if (1.0f <= TmpValue && TmpValue < 1.5f)
		{
			RendererVector_[4]->SetIndex(5);
		}
		else if (1.5f <= TmpValue && TmpValue < 2.0f)
		{
			RendererVector_[4]->SetIndex(4);
		}
		else if (2.0f <= TmpValue && TmpValue < 2.5f)
		{
			RendererVector_[4]->SetIndex(3);
		}
		else if (2.5f <= TmpValue && TmpValue < 3.0f)
		{
			RendererVector_[4]->SetIndex(2);
		}
		else if (3.0f <= TmpValue && TmpValue < 3.5f)
		{
			RendererVector_[4]->SetIndex(1);
		}
		else if (3.5f <= TmpValue)
		{
			RendererVector_[4]->SetIndex(0);
		}
	}

	// 럭
	{
		float TmpValue = Player::MainPlayer->GetLuck();
		if (TmpValue < 1.5f)
		{
			RendererVector_[5]->SetIndex(13);
		}
		if (1.5f <= TmpValue && TmpValue < 2.5f)
		{
			RendererVector_[5]->SetIndex(12);
		}
		else if (2.5f <= TmpValue && TmpValue < 3.5f)
		{
			RendererVector_[5]->SetIndex(11);
		}
		else if (3.5f <= TmpValue && TmpValue < 4.5f)
		{
			RendererVector_[5]->SetIndex(10);
		}
		else if (4.5f <= TmpValue && TmpValue < 5.5f)
		{
			RendererVector_[5]->SetIndex(9);
		}
		else if (5.5f <= TmpValue && TmpValue < 6.5f)
		{
			RendererVector_[5]->SetIndex(8);
		}
		else if (6.5f <= TmpValue)
		{
			RendererVector_[5]->SetIndex(7);
		}
	}
}

void PauseUI::TurnOn(bool _On)
{
	IsPause_ = _On;
	if (_On)
	{
		On();
	}
	else
	{
		Off();
	}
}

void PauseUI::Start()
{
	// 화면
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("bgblack.bmp");
		TmpRenderer->SetPivot(GameEngineWindow::GetScale().Half());
		TmpRenderer->SetAlpha(150);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("pausescreen.bmp");
		TmpRenderer->SetPivot(GameEngineWindow::GetScale().Half());
	}

	// 수치
	// 인덱스 0 ~ 6은 오른쪽으로 기울어진수치, 7 ~ 13은 왼쪽으로 기울어진 수치이다
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("pausescreen_Value.bmp");
		TmpRenderer->SetPivot(GameEngineWindow::GetScale().Half() + float4(-65, -127));
		TmpRenderer->SetIndex(1);
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("pausescreen_Value.bmp");
		TmpRenderer->SetPivot(GameEngineWindow::GetScale().Half() + float4(-65, -77));
		TmpRenderer->SetIndex(7);
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("pausescreen_Value.bmp");
		TmpRenderer->SetPivot(GameEngineWindow::GetScale().Half() + float4(-65, -26));
		TmpRenderer->SetIndex(0);
		RendererVector_.push_back(TmpRenderer);
	}

	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("pausescreen_Value.bmp");
		TmpRenderer->SetPivot(GameEngineWindow::GetScale().Half() + float4(112, -128));
		TmpRenderer->SetIndex(7);
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("pausescreen_Value.bmp");
		TmpRenderer->SetPivot(GameEngineWindow::GetScale().Half() + float4(112, -77));
		TmpRenderer->SetIndex(0);
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("pausescreen_Value.bmp");
		TmpRenderer->SetPivot(GameEngineWindow::GetScale().Half() + float4(112, -26));
		TmpRenderer->SetIndex(7);
		RendererVector_.push_back(TmpRenderer);
	}

	// 화살표
	ArrowPosVector_.push_back(GameEngineWindow::GetScale().Half() + float4(-210, 140));
	ArrowPosVector_.push_back(GameEngineWindow::GetScale().Half() + float4(-170, 210));
	{
		ArrowRenderer_ = CreateRenderer("pausescreen_Arrow.bmp");
		ArrowRenderer_->SetPivot(ArrowPosVector_[ArrowIndex_]);
	}

	if (false == GameEngineInput::GetInst()->IsKey("PauseUp"))
	{
		GameEngineInput::GetInst()->CreateKey("PauseUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("PauseDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("PauseSpace", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("PauseEnter", VK_RETURN);
	}

	//Off();
}

void PauseUI::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("PauseUp"))
	{
		AddArrowIndex(-1);
	}

	if (true == GameEngineInput::GetInst()->IsDown("PauseDown"))
	{
		AddArrowIndex(1);
	}

	if (true == GameEngineInput::GetInst()->IsDown("PauseSpace") || true == GameEngineInput::GetInst()->IsDown("PauseEnter"))
	{

	}
}

void PauseUI::AddArrowIndex(int _Value)
{
	ArrowIndex_ += _Value;
	if (ArrowIndex_ > 1)
	{
		ArrowIndex_ = 0;
	}
	if (ArrowIndex_ < 0)
	{
		ArrowIndex_ = 1;
	}

	ArrowRenderer_->SetPivot(ArrowPosVector_[ArrowIndex_]);
}

void PauseUI::Select(int _Index)
{
	if (_Index == 0)
	{
		GameEngineTime::SetPause(false);
	}
	else if (_Index == 1)
	{
		GameEngine::GetInst().ChangeLevel("Loading");
	}
}
