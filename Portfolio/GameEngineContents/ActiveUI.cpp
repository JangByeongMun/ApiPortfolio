#include "ActiveUI.h"
#include "Player.h"

ActiveUI::ActiveUI() 
{
}

ActiveUI::~ActiveUI() 
{
}

void ActiveUI::SettingUI()
{
	switch (Player::MainPlayer->GetActiveType())
	{
	case ActiveType::Default:
		break;
	case ActiveType::Item034:
		SelectItemRenderer(0);
		SelectGazeRenderer(2);
		break;
	case ActiveType::Item036:
		SelectItemRenderer(1);
		SelectGazeRenderer(1);
		break;
	case ActiveType::Item045:
		SelectItemRenderer(2);
		SelectGazeRenderer(3);
		break;
	case ActiveType::Max:
		break;
	default:
		break;
	}
}

void ActiveUI::SetGaze(int _Value)
{
	switch (Player::MainPlayer->GetActiveType())
	{
	case ActiveType::Default:
		break;
	case ActiveType::Item034:
		GazeRenderer[2]->SetIndex(_Value);
		break;
	case ActiveType::Item036:
		GazeRenderer[1]->SetIndex(_Value);
		break;
	case ActiveType::Item045:
		GazeRenderer[3]->SetIndex(_Value);
		break;
	case ActiveType::Max:
		break;
	default:
		break;
	}
}


void ActiveUI::Start()
{
	SetPosition({ 50, 40 });

	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("collectibles_034_thebookofbelial.bmp");
		TmpRenderer->CameraEffectOff();
		TmpRenderer->Off();
		ItemRenderer.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("collectibles_036_thepoop.bmp");
		TmpRenderer->CameraEffectOff();
		TmpRenderer->Off();
		ItemRenderer.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("collectibles_045_yumheart.bmp");
		TmpRenderer->CameraEffectOff();
		TmpRenderer->Off();
		ItemRenderer.push_back(TmpRenderer);
	}
	
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("ui_chargebar_Base.bmp");
		TmpRenderer->SetPivot({ 50, 10 });
		TmpRenderer->CameraEffectOff();
		TmpRenderer->Off();
		GazeRenderer.push_back(TmpRenderer);
	}

	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("ui_chargebar_1.bmp");
		TmpRenderer->SetPivot({ 50, 10 });
		TmpRenderer->SetIndex(0);
		TmpRenderer->CameraEffectOff();
		TmpRenderer->Off();
		GazeRenderer.push_back(TmpRenderer);
	}
	
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("ui_chargebar_3.bmp");
		TmpRenderer->SetPivot({ 50, 10 });
		TmpRenderer->SetIndex(0);
		TmpRenderer->CameraEffectOff();
		TmpRenderer->Off();
		GazeRenderer.push_back(TmpRenderer);
	}
	
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("ui_chargebar_4.bmp");
		TmpRenderer->SetPivot({ 50, 10 });
		TmpRenderer->SetIndex(0);
		TmpRenderer->CameraEffectOff();
		TmpRenderer->Off();
		GazeRenderer.push_back(TmpRenderer);
	}
}

void ActiveUI::SelectItemRenderer(int _Value)
{
	for (int i = 0; i < ItemRenderer.size(); i++)
	{
		if (i == _Value)
		{
			ItemRenderer[i]->On();
		}
		else
		{
			ItemRenderer[i]->Off();
		}
	}
}

void ActiveUI::SelectGazeRenderer(int _Value)
{
	for (int i = 0; i < GazeRenderer.size(); i++)
	{
		if (i == 0 || i == _Value)
		{
			GazeRenderer[i]->On();
		}
		else
		{
			GazeRenderer[i]->Off();
		}
	}
}
