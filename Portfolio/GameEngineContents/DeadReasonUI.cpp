#include "DeadReasonUI.h"
#include "ContentsGlobal.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>

DeadReasonUI::DeadReasonUI()
{
}

DeadReasonUI::~DeadReasonUI()
{
}

void DeadReasonUI::Start()
{
	SetPosition(GetCameraEffectPosition() + GameEngineWindow::GetScale().Half());
	CreateRenderer("death_portraits.bmp")->CameraEffectOff();

	switch (SelectedCharacterType)
	{
	case CharacterType::ISAAC:
		CreateRenderer("death_portraits_3_isaac.bmp")->CameraEffectOff();
		break;
	case CharacterType::CAIN:
		CreateRenderer("death_portraits_3_cain.bmp")->CameraEffectOff();
		break;
	case CharacterType::MAGDALENE:
		CreateRenderer("death_portraits_3_magdalene.bmp")->CameraEffectOff();
		break;
	case CharacterType::JUDAS:
		CreateRenderer("death_portraits_3_judas.bmp")->CameraEffectOff();
		break;
	case CharacterType::BLUEBABY:
		CreateRenderer("death_portraits_3_bluebaby.bmp")->CameraEffectOff();
		break;
	default:
		break;
	}

	int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, 12);
	GameEngineRenderer* Renderer = CreateRenderer("death_portraits_1.bmp", static_cast<int>(ORDER::UI));
	Renderer->SetIndex(RandomInt);
	Renderer->CameraEffectOff();
}

void DeadReasonUI::Update()
{
}

