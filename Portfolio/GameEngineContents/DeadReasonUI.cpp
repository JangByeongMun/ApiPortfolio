#include "DeadReasonUI.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "ContentsGlobal.h"
#include "RandomRoomManager.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>
#include "ContentsGlobal.h"

DeadReasonUI::DeadReasonUI()
{
}

DeadReasonUI::~DeadReasonUI()
{
}

void DeadReasonUI::Start()
{
	GameEngineSound::SoundPlayOneShotWithVolume("you died.ogg", 0, 1.0f * Option_MUSIC);

	float4 TestPos = GetLevel()->GetCameraPos() + GameEngineWindow::GetScale().Half();
	SetPosition(TestPos);
	CreateRenderer("bgblack.bmp", static_cast<int>(ORDER::UI))->SetAlpha(100);
	CreateRenderer("death_portraits.bmp", static_cast<int>(ORDER::UI));

	switch (SelectedCharacterType)
	{
	case CharacterType::ISAAC:
		CreateRenderer("death_portraits_3_isaac.bmp", static_cast<int>(ORDER::UI))->SetPivot({90, 290});
		break;
	case CharacterType::CAIN:
		CreateRenderer("death_portraits_3_cain.bmp", static_cast<int>(ORDER::UI))->SetPivot({ 90, 290 });
		break;
	case CharacterType::MAGDALENE:
		CreateRenderer("death_portraits_3_magdalene.bmp", static_cast<int>(ORDER::UI))->SetPivot({ 90, 290 });
		break;
	case CharacterType::JUDAS:
		CreateRenderer("death_portraits_3_judas.bmp", static_cast<int>(ORDER::UI))->SetPivot({ 90, 290 });
		break;
	case CharacterType::BLUEBABY:
		CreateRenderer("death_portraits_3_bluebaby.bmp", static_cast<int>(ORDER::UI))->SetPivot({ 90, 290 });
		break;
	default:
		break;
	}

	switch (RandomRoomManager::GetInst()->GetCurrentFloor())
	{
	case 1:
		CreateRenderer("death_portraits_2_1.bmp", static_cast<int>(ORDER::UI))->SetPivot({ -100, -27 });
		break;
	case 2:
		CreateRenderer("death_portraits_2_2.bmp", static_cast<int>(ORDER::UI))->SetPivot({ -100, -27 });
		break;
	case 3:
		CreateRenderer("death_portraits_2_3.bmp", static_cast<int>(ORDER::UI))->SetPivot({ -100, -27 });
		break;
	default:
		break;
	}

	{
		int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, 12);
		GameEngineRenderer* Renderer = CreateRenderer("death_portraits_1.bmp", static_cast<int>(ORDER::UI));
		Renderer->SetIndex(RandomInt);
		Renderer->SetPivot({ 200, -210 });
	}
	
	{
		int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, 2);
		GameEngineRenderer* Renderer = CreateRenderer("death_items.bmp", static_cast<int>(ORDER::UI));
		Renderer->SetIndex(RandomInt);
		Renderer->SetPivot({ 90, -40 });
	}

	if (false == GameEngineInput::GetInst()->IsKey("ResetSpace"))
	{
		GameEngineInput::GetInst()->CreateKey("ResetESC", VK_ESCAPE);
		GameEngineInput::GetInst()->CreateKey("ResetSpace", VK_SPACE);
	}
}

void DeadReasonUI::Update()
{
	if (
		true == GameEngineInput::GetInst()->IsDown("ResetESC") ||
		true == GameEngineInput::GetInst()->IsDown("ResetSpace")
		)
	{
		GameEngineTime::SetPause(false);
		GameEngine::GetInst().ChangeLevel("Menu");
	}
}