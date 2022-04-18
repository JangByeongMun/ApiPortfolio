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
	TmpRenderer->CameraEffectOff();

	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("ui_chargebar_1.bmp");
		TmpRenderer->SetPivot({ 50, 10 });
		TmpRenderer->SetIndex(0);
		TmpRenderer->CameraEffectOff();
	}

	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("ui_chargebar_1.bmp");
		TmpRenderer->SetPivot({ 50, 10 });
		TmpRenderer->SetIndex(3);
		TmpRenderer->CameraEffectOff();
	}
}

