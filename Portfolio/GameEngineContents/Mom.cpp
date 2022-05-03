#include "Mom.h"
#include "Player.h"
#include "Gusher.h"
#include "Pooter.h"
#include "Clotty.h"
#include "Fly.h"
#include "RoomActor.h"
#include "Player.h"
#include "PlayerHP.h"

Mom::Mom() 
	: State_(MomState::Idle)
	, LegRenderer_(nullptr)
	, LegShadowRenderer_(nullptr)
	, LegCollision_(nullptr)
	, AnimTimer_(0.0f)
	, IsAnim_(false)
	, HandCheck_(-1)
{
}

Mom::~Mom() 
{
}

void Mom::Start()
{
	Type_ = BossType::Mom;
	SetHP(645.0f);
	SetAttackDelay(0.5f);

	// ¹®
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("boss_054_mom_Door_Up.bmp");
		TmpRenderer->SetIndex(1);
		TmpRenderer->SetPivot({ 0, -300 });
		DoorRenderers_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("boss_054_mom_Door_Down.bmp");
		TmpRenderer->SetIndex(1);
		TmpRenderer->SetPivot({ 0, 300 });
		DoorRenderers_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("boss_054_mom_Door_Left.bmp");
		TmpRenderer->SetIndex(1);
		TmpRenderer->SetPivot({ -500, 0 });
		DoorRenderers_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("boss_054_mom_Door_Right.bmp");
		TmpRenderer->SetIndex(1);
		TmpRenderer->SetPivot({ 500, 0 });
		DoorRenderers_.push_back(TmpRenderer);
	}

	// ´«·»´õ·¯
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer(static_cast<int>(ORDER::PLAYER));
		TmpRenderer->CreateAnimation("boss_054_mom_Eye_Up.bmp", "Eye_1", 0, 0, 0.1f, false);
		TmpRenderer->CreateAnimation("boss_054_mom_Eye_Up.bmp", "Eye_2", 1, 1, 0.1f, false);
		TmpRenderer->CreateAnimation("boss_054_mom_Eye_Up.bmp", "Eye_3", 2, 2, 0.1f, false);
		TmpRenderer->CreateAnimation("None.bmp", "None", 0, 0, 0.1f, false);
		TmpRenderer->ChangeAnimation("None");
		TmpRenderer->SetPivot({0, -270});
		EyeRenderers_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer(static_cast<int>(ORDER::PLAYER));
		TmpRenderer->CreateAnimation("boss_054_mom_Eye_Down.bmp", "Eye_1", 0, 0, 0.1f, false);
		TmpRenderer->CreateAnimation("boss_054_mom_Eye_Down.bmp", "Eye_2", 1, 1, 0.1f, false);
		TmpRenderer->CreateAnimation("boss_054_mom_Eye_Down.bmp", "Eye_3", 2, 2, 0.1f, false);
		TmpRenderer->CreateAnimation("None.bmp", "None", 0, 0, 0.1f, false);
		TmpRenderer->ChangeAnimation("None");
		TmpRenderer->SetPivot({ 0, 270 });
		EyeRenderers_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer(static_cast<int>(ORDER::PLAYER));
		TmpRenderer->CreateAnimation("boss_054_mom_Eye_Left.bmp", "Eye_1", 0, 0, 0.1f, false);
		TmpRenderer->CreateAnimation("boss_054_mom_Eye_Left.bmp", "Eye_2", 1, 1, 0.1f, false);
		TmpRenderer->CreateAnimation("boss_054_mom_Eye_Left.bmp", "Eye_3", 2, 2, 0.1f, false);
		TmpRenderer->CreateAnimation("None.bmp", "None", 0, 0, 0.1f, false);
		TmpRenderer->ChangeAnimation("None");
		TmpRenderer->SetPivot({ -470, 0 });
		EyeRenderers_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer(static_cast<int>(ORDER::PLAYER));
		TmpRenderer->CreateAnimation("boss_054_mom_Eye_Right.bmp", "Eye_1", 0, 0, 0.1f, false);
		TmpRenderer->CreateAnimation("boss_054_mom_Eye_Right.bmp", "Eye_2", 1, 1, 0.1f, false);
		TmpRenderer->CreateAnimation("boss_054_mom_Eye_Right.bmp", "Eye_3", 2, 2, 0.1f, false);
		TmpRenderer->CreateAnimation("None.bmp", "None", 0, 0, 0.1f, false);
		TmpRenderer->ChangeAnimation("None");
		TmpRenderer->SetPivot({ 470, 0 });
		EyeRenderers_.push_back(TmpRenderer);
	}

	// ¼Õ·»´õ·¯
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer(static_cast<int>(ORDER::PLAYER));
		TmpRenderer->CreateAnimation("boss_054_mom_Hand_Up.bmp", "Hand", 0, 1, 0.3f, false);
		TmpRenderer->CreateAnimation("None.bmp", "None", 0, 0, 0.1f, false);
		TmpRenderer->ChangeAnimation("None");
		TmpRenderer->SetPivot({ 0, -200 });
		HandRenderers_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer(static_cast<int>(ORDER::PLAYER));
		TmpRenderer->CreateAnimation("boss_054_mom_Hand_Down.bmp", "Hand", 0, 1, 0.3f, false);
		TmpRenderer->CreateAnimation("None.bmp", "None", 0, 0, 0.1f, false);
		TmpRenderer->ChangeAnimation("None");
		TmpRenderer->SetPivot({ 0, 200 });
		HandRenderers_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer(static_cast<int>(ORDER::PLAYER));
		TmpRenderer->CreateAnimation("boss_054_mom_Hand_Left.bmp", "Hand", 0, 1, 0.3f, false);
		TmpRenderer->CreateAnimation("None.bmp", "None", 0, 0, 0.1f, false);
		TmpRenderer->ChangeAnimation("None");
		TmpRenderer->SetPivot({ -400, 0 });
		HandRenderers_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer(static_cast<int>(ORDER::PLAYER));
		TmpRenderer->CreateAnimation("boss_054_mom_Hand_Right.bmp", "Hand", 0, 1, 0.3f, false);
		TmpRenderer->CreateAnimation("None.bmp", "None", 0, 0, 0.1f, false);
		TmpRenderer->ChangeAnimation("None");
		TmpRenderer->SetPivot({ 400, 0 });
		HandRenderers_.push_back(TmpRenderer);
	}

	LegShadowRenderer_ = CreateRenderer("shadow.bmp", static_cast<int>(ORDER::BACKGROUND));
	LegShadowRenderer_->SetAlpha(70);
	LegShadowRenderer_->SetScale({ 300, 120 });
	LegShadowRenderer_->SetPivot({ 0, 90 });
	LegShadowRenderer_->Off();

	LegRenderer_ = CreateRenderer("boss_054_mom_Leg.bmp", static_cast<int>(ORDER::UI));
	LegRenderer_->Off();

	LegCollision_ = CreateCollision("Monster", {300, 200});
	LegCollision_->Off();

	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Monster", { 100, 100 }, {0, -260});
		TmpCollision_->Off();
		EyeCollision_.push_back(TmpCollision_);
	}
	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Monster", { 100, 100 }, { 0, 260 });
		TmpCollision_->Off();
		EyeCollision_.push_back(TmpCollision_);
	}
	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Monster", { 100, 100 }, { -460, 0 });
		TmpCollision_->Off();
		EyeCollision_.push_back(TmpCollision_);
	}
	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Monster", { 100, 100 }, { 460, 0 });
		TmpCollision_->Off();
		EyeCollision_.push_back(TmpCollision_);
	}

	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Monster", { 200, 200 }, { 0, -200 });
		TmpCollision_->Off();
		HandCollision_.push_back(TmpCollision_);
	}
	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Monster", { 200, 200 }, { 0, 200 });
		TmpCollision_->Off();
		HandCollision_.push_back(TmpCollision_);
	}
	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Monster", { 200, 200 }, { -400, 0 });
		TmpCollision_->Off();
		HandCollision_.push_back(TmpCollision_);
	}
	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Monster", { 200, 200 }, { 400, 0 });
		TmpCollision_->Off();
		HandCollision_.push_back(TmpCollision_);
	}

	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Check", { 200, 200 }, { 0, -200 });
		HandCheckCollision_.push_back(TmpCollision_);
	}
	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Check", { 200, 200 }, { 0, 200 });
		HandCheckCollision_.push_back(TmpCollision_);
	}
	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Check", { 200, 200 }, { -400, 0 });
		HandCheckCollision_.push_back(TmpCollision_);
	}
	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Check", { 200, 200 }, { 400, 0 });
		HandCheckCollision_.push_back(TmpCollision_);
	}
}

void Mom::MonsterUpdate()
{
	StateUpdate();
	CollisionCheck();
}

void Mom::MonsterDeath()
{
	ChangeState(MomState::Dead);
}

void Mom::ChangeState(MomState _State)
{
	if (State_ == _State)
	{
		return;
	}

	State_ = _State;
	switch (State_)
	{
	case MomState::Idle:
		IdleStart();
		break;
	case MomState::Hand:
		HandStart();
		break;
	case MomState::Leg:
		LegStart();
		break;
	case MomState::Summon:
		SummonStart();
		break;
	case MomState::Dead:
		DeadStart();
		break;
	default:
		break;
	}
}
void Mom::StateUpdate()
{
	switch (State_)
	{
	case MomState::Idle:
		IdleUpdate();
		break;
	case MomState::Hand:
		HandUpdate();
		break;
	case MomState::Leg:
		LegUpdate();
		break;
	case MomState::Summon:
		SummonUpdate();
		break;
	case MomState::Dead:
		DeadUpdate();
		break;
	default:
		break;
	}
}
void Mom::CollisionCheck()
{
	if (true == LegCollision_->IsUpdate() && true == LegCollision_->CollisionCheckRect("Player"))
	{
		Player::MainPlayer->GetPlayerHP()->MinusHearts(false);
	}

	for (int i = 0; i < EyeCollision_.size(); i++)
	{
		if (true == EyeCollision_[i]->IsUpdate() && true == EyeCollision_[i]->CollisionCheckRect("Player"))
		{
			Player::MainPlayer->GetPlayerHP()->MinusHearts(true);
		}
	}

	for (int i = 0; i < HandCollision_.size(); i++)
	{
		if (true == HandCollision_[i]->IsUpdate() && true == HandCollision_[i]->CollisionCheckRect("Player"))
		{
			Player::MainPlayer->GetPlayerHP()->MinusHearts(true);
		}
	}
}

void Mom::IdleStart()
{
	ResetValue();
}
void Mom::HandStart()
{
	ResetValue();
	AnimTimer_ = 0.0f;

	HandCollision_[HandCheck_]->On();
	HandRenderers_[HandCheck_]->On();
	HandRenderers_[HandCheck_]->ChangeAnimation("Hand");
}
void Mom::LegStart()
{
	ResetValue();
	AnimTimer_ = 0.0f;

	LegShadowRenderer_->On();
}
void Mom::SummonStart()
{
	ResetValue();
	AnimTimer_ = 0.0f;
	IsAnim_ = false;
	for (int i = 0; i < 3; i++)
	{
		int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, 3);
		DoorRenderers_[RandomInt]->SetIndex(0);
		EyeRenderers_[RandomInt]->On();
		EyeRenderers_[RandomInt]->ChangeAnimation("Eye_" + std::to_string(GameEngineRandom::MainRandom->RandomInt(1, 3)));
		EyeCollision_[RandomInt]->On();
	}
}
void Mom::DeadStart()
{
	ResetValue();
	AnimTimer_ = 0.0f;
}

void Mom::IdleUpdate()
{
	AttackTimer_ += GameEngineTime::GetDeltaTime();
	if (AttackTimer_ >= AttackDelay_)
	{
		AttackTimer_ = 0.0f;
		int RandomInt = -1;
		HandCheck_ = HandCheck();
		if (-1 == HandCheck())
		{
			RandomInt = GameEngineRandom::MainRandom->RandomInt(2, 3);
		}
		else
		{
			RandomInt = GameEngineRandom::MainRandom->RandomInt(1, 3);
		}
		ChangeState(static_cast<MomState>(RandomInt));
	}
}
void Mom::HandUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();

	if (1.0f <= AnimTimer_)
	{
		HandCollision_[HandCheck_]->Off();
		HandRenderers_[HandCheck_]->Off();
		HandRenderers_[HandCheck_]->ChangeAnimation("None");
		HandCheck_ = -1;
		ChangeState(MomState::Idle);
	}
}
void Mom::LegUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (0.0f <= AnimTimer_ && AnimTimer_ < 2.0f)
	{
		LegShadowRenderer_->SetPivot(Player::MainPlayer->GetPosition() - GetPosition() + float4(0, 20));
	}
	else if (2.5f <= AnimTimer_ && AnimTimer_ < 3.5f)
	{
		float4 LerpPos = float4::Lerp({ 100, -1000 }, {100, -470}, (AnimTimer_ - 2.5f) * 3.0f);
		LegRenderer_->On();
		LegRenderer_->SetPivot(LegShadowRenderer_->GetPivot() + LerpPos);
		LegShadowRenderer_->SetAlpha(float4::LerpFloat(50, 90, (AnimTimer_ - 2.5f) * 3.0f));
	}
	if (2.7f <= AnimTimer_ && AnimTimer_ < 3.0f)
	{
		LegCollision_->On();
		LegCollision_->SetPivot(LegShadowRenderer_->GetPivot());
	}

	if (4.0f <= AnimTimer_ && AnimTimer_ < 5.0f)
	{
		LegCollision_->Off();
		LegCollision_->SetPivot(LegShadowRenderer_->GetPivot());
		float4 LerpPos = float4::Lerp({ 100, -470 }, { 70, -1000 }, (AnimTimer_ - 4.0f) * 3.0f);
		LegRenderer_->SetPivot(LegShadowRenderer_->GetPivot() + LerpPos);
		LegShadowRenderer_->SetAlpha(float4::LerpFloat(90, 50, (AnimTimer_ - 4.0f) * 3.0f));
	}

	if (4.5f <= AnimTimer_)
	{
		LegRenderer_->Off();
		LegShadowRenderer_->Off();
		ChangeState(MomState::Idle);
	}
}
void Mom::SummonUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (1.5f <= AnimTimer_ && IsAnim_ == false)
	{
		IsAnim_ = true;
		for (int i = 0; i < EyeRenderers_.size(); i++)
		{
			float4 AddPivot;
			if (i == 0)
			{
				AddPivot = { 0, 30 };
			}
			if (i == 1)
			{
				AddPivot = { 0, -60 };
			}
			if (i == 2)
			{
				AddPivot = { 50, 0 };
			}
			if (i == 3)
			{
				AddPivot = { -50, 0 };
			}

			if (true == EyeRenderers_[i]->IsUpdate())
			{
				int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, 3);
				if (RandomInt == 0)
				{
					Gusher* TmpMonster = GetLevel()->CreateActor<Gusher>();
					TmpMonster->SetPosition(EyeRenderers_[i]->GetPivot() + GetPosition() + AddPivot);
					TmpMonster->SetRoom(*Room_);
				
					Room_->AddMonster(TmpMonster);
					Room_->AddMonsterCount();
				}
				else if (RandomInt == 1)
				{
					Pooter* TmpMonster = GetLevel()->CreateActor<Pooter>();
					TmpMonster->SetPosition(EyeRenderers_[i]->GetPivot() + GetPosition() + AddPivot);
					TmpMonster->SetRoom(*Room_);

					Room_->AddMonster(TmpMonster);
					Room_->AddMonsterCount();
				}
				else if (RandomInt == 2)
				{
					Fly* TmpMonster = GetLevel()->CreateActor<Fly>();
					TmpMonster->SetPosition(EyeRenderers_[i]->GetPivot() + GetPosition() + AddPivot);
					TmpMonster->SetRoom(*Room_);
					TmpMonster->SetType(FlyType::Red);

					Room_->AddMonster(TmpMonster);
					Room_->AddMonsterCount();
				}
				else if (RandomInt == 3)
				{
					Clotty* TmpMonster = GetLevel()->CreateActor<Clotty>();
					TmpMonster->SetPosition(EyeRenderers_[i]->GetPivot() + GetPosition() + AddPivot);
					TmpMonster->SetRoom(*Room_);

					Room_->AddMonster(TmpMonster);
					Room_->AddMonsterCount();
				}
			}
		}
		ChangeState(MomState::Idle);
	}
}
void Mom::DeadUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (AnimTimer_ >= 1.4f)
	{
		Death();
		return;
	}
	else if (AnimTimer_ >= 0.9f)
	{
		if (true == IsAnim_)
		{
			IsAnim_ = false;
			GameEngineRenderer* TmpRenderer = CreateRenderer("effect_002_bloodpoof.bmp", static_cast<int>(ORDER::FRONTUI));
			TmpRenderer->CreateAnimation("effect_002_bloodpoof.bmp", "effect_002_bloodpoof", 0, 15, 0.04f, false);
			TmpRenderer->ChangeAnimation("effect_002_bloodpoof");
			TmpRenderer->SetPivot({ GameEngineRandom::MainRandom->RandomFloat(-85, 85), GameEngineRandom::MainRandom->RandomFloat(-85, 85) });
		}
		return;
	}
	else if (AnimTimer_ >= 0.6f)
	{
		if (false == IsAnim_)
		{
			IsAnim_ = true;
			GameEngineRenderer* TmpRenderer = CreateRenderer("effect_002_bloodpoof.bmp", static_cast<int>(ORDER::FRONTUI));
			TmpRenderer->CreateAnimation("effect_002_bloodpoof.bmp", "effect_002_bloodpoof", 0, 15, 0.04f, false);
			TmpRenderer->ChangeAnimation("effect_002_bloodpoof");
			TmpRenderer->SetPivot({ GameEngineRandom::MainRandom->RandomFloat(-85, 85), GameEngineRandom::MainRandom->RandomFloat(-85, 85) });
		}
		return;
	}
	else if (AnimTimer_ >= 0.3f)
	{
		if (true == IsAnim_)
		{
			IsAnim_ = false;
			GameEngineRenderer* TmpRenderer = CreateRenderer("effect_002_bloodpoof.bmp", static_cast<int>(ORDER::FRONTUI));
			TmpRenderer->CreateAnimation("effect_002_bloodpoof.bmp", "effect_002_bloodpoof", 0, 15, 0.04f, false);
			TmpRenderer->ChangeAnimation("effect_002_bloodpoof");
			TmpRenderer->SetPivot({ GameEngineRandom::MainRandom->RandomFloat(-85, 85), GameEngineRandom::MainRandom->RandomFloat(-85, 85) });
		}

		return;
	}
}

void Mom::ResetValue()
{
	for (int i = 0; i < DoorRenderers_.size(); i++)
	{
		DoorRenderers_[i]->SetIndex(1);
	}
	for (int i = 0; i < EyeRenderers_.size(); i++)
	{
		EyeRenderers_[i]->Off();
	}
	for (int i = 0; i < HandRenderers_.size(); i++)
	{
		HandRenderers_[i]->Off();
	}

	LegRenderer_->Off();
	LegShadowRenderer_->Off();

	for (int i = 0; i < EyeCollision_.size(); i++)
	{
		EyeCollision_[i]->Off();
	}

	for (int i = 0; i < HandCollision_.size(); i++)
	{
		HandCollision_[i]->Off();
	}
}
int Mom::HandCheck()
{
	for (int i = 0; i < HandCheckCollision_.size(); i++)
	{
		if (true == HandCheckCollision_[i]->CollisionCheckRect("Player"))
		{
			return i;
		}
	}
	return -1;
}
