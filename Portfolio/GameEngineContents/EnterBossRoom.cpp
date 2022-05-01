#include "EnterBossRoom.h"
#include <GameEngineBase/GameEngineSound.h>
#include "ContentsGlobal.h"

EnterBossRoom::EnterBossRoom() 
	: AnimTimer_(0.0f)
{
}

EnterBossRoom::~EnterBossRoom() 
{
}

void EnterBossRoom::Setting()
{
	switch (SelectedCharacterType)
	{
	case CharacterType::ISAAC:
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("playerportrait_01_isaac.bmp", static_cast<int>(ORDER::FRONTUI));
		TmpRenderer->SetPivot({ -200, 120 });
		PlayerRenderers_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("vsnames.bmp", static_cast<int>(ORDER::FRONTUI));
		TmpRenderer->SetPivot({ -200, -250 });
		TmpRenderer->SetIndex(0);
		PlayerRenderers_.push_back(TmpRenderer);
	}
	break;
	case CharacterType::CAIN:
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("playerportrait_03_cain.bmp", static_cast<int>(ORDER::FRONTUI));
		TmpRenderer->SetPivot({ -200, 120 });
		PlayerRenderers_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("vsnames.bmp", static_cast<int>(ORDER::FRONTUI));
		TmpRenderer->SetPivot({ -200, -250 });
		TmpRenderer->SetIndex(20);
		PlayerRenderers_.push_back(TmpRenderer);
	}
	break;
	case CharacterType::MAGDALENE:
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("playerportrait_02_magdalene.bmp", static_cast<int>(ORDER::FRONTUI));
		TmpRenderer->SetPivot({ -200, 120 });
		PlayerRenderers_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("vsnames.bmp", static_cast<int>(ORDER::FRONTUI));
		TmpRenderer->SetPivot({ -200, -250 });
		TmpRenderer->SetIndex(25);
		PlayerRenderers_.push_back(TmpRenderer);
	}
	break;
	case CharacterType::JUDAS:
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("playerportrait_04_judas.bmp", static_cast<int>(ORDER::FRONTUI));
		TmpRenderer->SetPivot({ -200, 120 });
		PlayerRenderers_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("vsnames.bmp", static_cast<int>(ORDER::FRONTUI));
		TmpRenderer->SetPivot({ -200, -250 });
		TmpRenderer->SetIndex(30);
		PlayerRenderers_.push_back(TmpRenderer);
	}
	break;
	case CharacterType::BLUEBABY:
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("playerportrait_06_bluebaby.bmp", static_cast<int>(ORDER::FRONTUI));
		TmpRenderer->SetPivot({ -200, 120 });
		PlayerRenderers_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("vsnames.bmp", static_cast<int>(ORDER::FRONTUI));
		TmpRenderer->SetPivot({ -200, -250 });
		TmpRenderer->SetIndex(15);
		PlayerRenderers_.push_back(TmpRenderer);
	}
	break;
	default:
		break;
	}

	switch (SelectedBossType)
	{
	case BossType::Default:
		break;
	case BossType::Monstro:
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("portrait_20.0_monstro.bmp", static_cast<int>(ORDER::FRONTUI));
		TmpRenderer->SetPivot({ 200, 100 });
		BossRenderers_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("vsnames.bmp", static_cast<int>(ORDER::FRONTUI));
		TmpRenderer->SetPivot({ 200, -250 });
		TmpRenderer->SetIndex(1);
		BossRenderers_.push_back(TmpRenderer);
	}
	break;
	case BossType::Loki:
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("portrait_69.0_loki.bmp", static_cast<int>(ORDER::FRONTUI));
		TmpRenderer->SetPivot({ 200, 100 });
		BossRenderers_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("vsnames.bmp", static_cast<int>(ORDER::FRONTUI));
		TmpRenderer->SetPivot({ 200, -250 });
		TmpRenderer->SetIndex(28);
		BossRenderers_.push_back(TmpRenderer);
	}
	break;
	case BossType::Max:
		break;
	default:
		break;
	}


	//for (int i = 0; i < BossRenderers_.size(); i++)
	//{
	//	BossRenderers_[i]->Off();
	//}
}

void EnterBossRoom::Start()
{
	CreateRenderer("bgblack.bmp", static_cast<int>(ORDER::FRONTUI));

	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("playerspot_01_basement.bmp", static_cast<int>(ORDER::FRONTUI));
		TmpRenderer->SetPivot({ -200, 220 });
		PlayerRenderers_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("bossspot_01_basement.bmp", static_cast<int>(ORDER::FRONTUI));
		TmpRenderer->SetPivot({200, 250});
		BossRenderers_.push_back(TmpRenderer);
	}

	{
		GameEngineSound::SoundPlayOneShotWithVolume("castleportcullis.wav", 0, 0.01f * Option_SFX);
	}
}

void EnterBossRoom::Update()
{
	AnimTimer_ += GameEngineTime::GetUnstoppableDeltaTime();

	if (AnimTimer_ <= 0.5f)
	{
		for (int i = 0; i < PlayerRenderers_.size(); i++)
		{
			float4 LerpPos = float4(float4::LerpFloat(-700, -350, AnimTimer_ * 4.0f), PlayerRenderers_[i]->GetPivot().y);
			PlayerRenderers_[i]->SetPivot(LerpPos);
		}

		for (int i = 0; i < BossRenderers_.size(); i++)
		{
			float4 LerpPos = float4(float4::LerpFloat(700, 350, AnimTimer_ * 4.0f), BossRenderers_[i]->GetPivot().y);
			BossRenderers_[i]->SetPivot(LerpPos);
		}
	}
	else if (AnimTimer_ <= 1.0f)
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("vsnames_vs.bmp", static_cast<int>(ORDER::FRONTUI));
		TmpRenderer->SetPivot({ -20, -240 });
		TmpRenderer->SetAlpha(static_cast<unsigned int>(float4::LerpFloat(0.0f, 255.0f, (AnimTimer_ - 0.5f) * 4.0f)));
	}
	else
	{
		GameEngineTime::Pause();
		Death();
	}
}

