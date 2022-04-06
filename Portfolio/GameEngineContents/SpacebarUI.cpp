#include "SpacebarUI.h"

SpacebarUI::SpacebarUI() 
	: ItemRenderer(nullptr)
{
}

SpacebarUI::~SpacebarUI() 
{
}

void SpacebarUI::Start()
{
	SetPosition({ 50, 40 });

	GameEngineRenderer* TmpRenderer = CreateRenderer("collectibles_045_yumheart.bmp");
	
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("ui_chargebar_1.bmp");
		TmpRenderer->SetPivot({ 50, 10 });
		TmpRenderer->SetIndex(0);
	}

	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("ui_chargebar_1.bmp");
		TmpRenderer->SetPivot({ 50, 10 });
		TmpRenderer->SetIndex(3);
	}
}

