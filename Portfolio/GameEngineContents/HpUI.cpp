#include "HpUI.h"
#include <GameEngineBase/GameEngineWindow.h>

HpUI::HpUI()
	: RendererVector()
	, StartHP(3)
{
}

HpUI::~HpUI() 
{
}

void HpUI::Start()
{
	int MaxCount = 12;
	SetPosition({130, 35});
	RendererVector.reserve(MaxCount);

	for (int i = 0; i < MaxCount; i++)
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("ui_hearts_1.bmp");

		if (i < StartHP)
		{
			TmpRenderer->SetIndex(0);
		}
		else
		{
			TmpRenderer->SetIndex(9);
		}

		float x = static_cast<float>((i % (MaxCount / 2)) * 36);
		float y = static_cast<float>((i / (MaxCount / 2)) * 36);
		TmpRenderer->SetPivot({ x, y });
	}
}

