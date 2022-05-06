#include "Charger.h"
#include "Player.h"

Charger::Charger() 
	: IsAttack_(false)
	, Dir_(ChargerDir::None)
	, MoveDir_(float4::ZERO)
	, AnimTimer_(0.0f)
{
}

Charger::~Charger() 
{
}

void Charger::Start()
{
	Collision_ = CreateCollision("Monster", { 50, 50 });
	Renderer_ = CreateRenderer(static_cast<int>(ORDER::PLAYER));
	Renderer_->CreateAnimation("monster_113_charger_Left.bmp", "Idle_Up", 4, 7, 0.1f, true);
	Renderer_->CreateAnimation("monster_113_charger_Left.bmp", "Idle_Down", 8, 11, 0.1f, true);
	Renderer_->CreateAnimation("monster_113_charger_Left.bmp", "Idle_Left", 0, 3, 0.1f, true);
	Renderer_->CreateAnimation("monster_113_charger_Right.bmp", "Idle_Right", 0, 3, 0.1f, true);
	Renderer_->CreateAnimation("monster_113_charger_Left.bmp", "Attack_Up", 14, 14, 0.1f, false);
	Renderer_->CreateAnimation("monster_113_charger_Left.bmp", "Attack_Down", 12, 12, 0.1f, false);
	Renderer_->CreateAnimation("monster_113_charger_Left.bmp", "Attack_Left", 13, 13, 0.1f, false);
	Renderer_->CreateAnimation("monster_113_charger_Right.bmp", "Attack_Right", 13, 13, 0.1f, false);
	Renderer_->ChangeAnimation("Idle_Left");

	SetHP(10);
	SetMoveSpeed(100.0f);
	SetAttackDelay(2.0f);
}

void Charger::MonsterUpdate()
{
	if (true == IsAttack_)
	{
		switch (Dir_)
		{
		case ChargerDir::Up:
			Renderer_->ChangeAnimation("Attack_Up");
			MoveDir_ = float4::UP;
			break;
		case ChargerDir::Down:
			Renderer_->ChangeAnimation("Attack_Down");
			MoveDir_ = float4::DOWN;
			break;
		case ChargerDir::Left:
			Renderer_->ChangeAnimation("Attack_Left");
			MoveDir_ = float4::LEFT;
			break;
		case ChargerDir::Right:
			Renderer_->ChangeAnimation("Attack_Right");
			MoveDir_ = float4::RIGHT;
			break;
		default:
			break;
		}

		if (false == MonsterSetMoveToWalkReturn(MoveDir_ * GameEngineTime::GetDeltaTime() * MoveSpeed_ * 4.0f))
		{
			IsAttack_ = false;
		}
	}
	else
	{
		AttackTimer_ += GameEngineTime::GetDeltaTime();

		Dir_ = PlayerLine();
		if (ChargerDir::None != Dir_ && AttackDelay_ <= AttackTimer_) // 플레이어가 x, y축 안에 들어와있고 공격 딜레이가 지났을때
		{
			IsAttack_ = true;
			AttackTimer_ = 0.0f;
		}
		else
		{
			AnimTimer_ += GameEngineTime::GetDeltaTime();
			if (AnimTimer_ >= 2.0f)
			{
				AnimTimer_ = 0.0f;
				MoveDir_ = float4(GameEngineRandom::MainRandom->RandomFloat(-2, 2), GameEngineRandom::MainRandom->RandomFloat(-2, 2));
				int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, 1);
				if (0 == RandomInt)
				{
					MoveDir_.x = 0;
					if (MoveDir_.y >= 0)
					{
						Renderer_->ChangeAnimation("Idle_Down");
					}
					else
					{
						Renderer_->ChangeAnimation("Idle_Up");
					}
				}
				else
				{
					MoveDir_.y = 0;
					if (MoveDir_.x >= 0)
					{
						Renderer_->ChangeAnimation("Idle_Right");
					}
					else
					{
						Renderer_->ChangeAnimation("Idle_Left");
					}
				}
				MoveDir_.Normal2D();
			}

			if (false == MonsterSetMoveToWalkReturn(MoveDir_ * GameEngineTime::GetDeltaTime() * MoveSpeed_))
			{
				AnimTimer_ += 2.0f;
			}
		}
	}
}

ChargerDir Charger::PlayerLine()
{
	if (std::abs(Player::MainPlayer->GetPosition().x - GetPosition().x) <= 10.0f )
	{
		if (Player::MainPlayer->GetPosition().y >= GetPosition().y)
		{
			return ChargerDir::Down;
		}
		else
		{
			return ChargerDir::Up;
		}
	}
	else if (std::abs(Player::MainPlayer->GetPosition().y - GetPosition().y) <= 10.0f)
	{
		if (Player::MainPlayer->GetPosition().x >= GetPosition().x)
		{
			return ChargerDir::Right;
		}
		else
		{
			return ChargerDir::Left;
		}
	}

	return ChargerDir::None;
}
