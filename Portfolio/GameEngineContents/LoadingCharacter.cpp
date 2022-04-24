#include "LoadingCharacter.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include "ContentsGlobal.h"

LoadingCharacter::LoadingCharacter() 
	: IsLeft(false)
	, StartX(0)

{
}

LoadingCharacter::~LoadingCharacter() 
{
}

void LoadingCharacter::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half() + float4{0, 190});
	StartX = GetPosition().x;
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

void LoadingCharacter::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	switch (SelectedCharacterType)
	{
	case CharacterType::ISAAC:
		CreateRenderer("Loading_01_isaac.bmp");
		break;
	case CharacterType::CAIN:
		CreateRenderer("Loading_03_cain.bmp");
		break;
	case CharacterType::MAGDALENE:
		CreateRenderer("Loading_02_magdalene.bmp");
		break;
	case CharacterType::JUDAS:
		CreateRenderer("Loading_04_judas.bmp");
		break;
	case CharacterType::BLUEBABY:
		CreateRenderer("Loading_06_bluebaby.bmp");
		break;
	default:
		break;
	}
}
