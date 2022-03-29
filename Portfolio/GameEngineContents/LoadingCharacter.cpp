#include "LoadingCharacter.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>

LoadingCharacter::LoadingCharacter() 
{
}

LoadingCharacter::~LoadingCharacter() 
{
}

void LoadingCharacter::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half() + float4{0, 190});
	StartX = GetPosition().x;

	CreateRenderer("Loading_01_isaac.bmp");
}

void LoadingCharacter::Update()
{
	if (IsLeft)
	{
		SetMove(float4(-100, 0) * GameEngineTime::GetInst()->GetDeltaTime());

		if (StartX - GetPosition().x >= 3.0f)
		{
			IsLeft = !IsLeft;
		}
	}
	else
	{
		SetMove(float4(100, 0) * GameEngineTime::GetInst()->GetDeltaTime());

		if (GetPosition().x - StartX >= 3.0f)
		{
			IsLeft = !IsLeft;
		}
	}
}

