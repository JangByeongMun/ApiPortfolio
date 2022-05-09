#include "Monster.h"
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "Player.h"
#include "RoomActor.h"
#include "RandomRoomManager.h"
#include "PlayLevel.h"
#include "RandomBlood.h"
#include "PlayerHP.h"

Monster::Monster()
	: Room_(nullptr)
	, Renderer_(nullptr)
	, Collision_(nullptr)
	, IsLeft_(true)
	, AttackTimer_(0.0f)
	, AttackDelay_(2.5f)
	, IsAttack_(true)
	, MoveSpeed_(100.0f)
	, HP_(0)
	, MaxHP_(0)
	, IsInvincibility_(false)
{
}

Monster::~Monster() 
{
}

void Monster::Start()
{
}

void Monster::Update()
{
	// ���� �濡 �ִ� ���͵鸸 ���� �����ϵ��� �ٸ����϶� return;
	if (false == Room_->IsCurrentRoom())
	{
		return;
	}

	IsLeft_ = AttackNormalDir().x <= 0;
	MonsterUpdate();

	// ���� �浹��
	if (nullptr != Collision_ && true == Collision_->CollisionCheckRect("Player"))
	{
		if (IsAttack_ == true)
		{
			Player::MainPlayer->GetPlayerHP()->MinusHearts(true);
		}
	}
}

///////////////////////////////// ����
float4 Monster::AttackNormalDir()
{
	float4 ReturnFloat4 = Player::MainPlayer->GetPosition() - GetPosition();
	ReturnFloat4.Normal2D();
	return ReturnFloat4;
}

///////////////////////////////// �̵�
void Monster::MonsterSetMoveToFly(float4 _Value)
{
	GameEngineImage* MapColImage_ = GameEngineImageManager::GetInst()->Find("basementTestCol.bmp");

	// �븶�� ũ��� �����Ƿ� ����ġ�� �༭ ��뿡���� �Ȱ��� ��ġ��ŭ�� �̵��Ҽ��ֵ���
	RoomActor* FindRoom = RandomRoomManager::GetInst()->GetCurrentRoom();
	float4 AddPivot = FindRoom->GetPosition() - GameEngineWindow::GetScale().Half();

	// x���̳� y������ ���̻� ����������� x�� y�� �ѱ����� �����ϰ� �̵�
	float4 NextPos = GetPosition() + _Value;
	float4 NextPos_x = GetPosition() + float4(_Value.x, 0);
	float4 NextPos_y = GetPosition() + float4(0, _Value.y);
	int Color = MapColImage_->GetImagePixel(NextPos - AddPivot);
	int Color_x = MapColImage_->GetImagePixel(NextPos_x - AddPivot);
	int Color_y = MapColImage_->GetImagePixel(NextPos_y - AddPivot);
	if (RGB(0, 0, 0) != Color)
	{
		SetMove(_Value);
	}
	else if (RGB(0, 0, 0) != Color_x)
	{
		SetMove(float4(_Value.x, 0));
	}
	else if (RGB(0, 0, 0) != Color_y)
	{
		SetMove(float4(0, _Value.y));
	}
}

void Monster::MonsterSetMoveToWalk(float4 _Value)
{
	GameEngineImage* MapColImage_ = GameEngineImageManager::GetInst()->Find("basementTestCol.bmp");

	// �븶�� ũ��� �����Ƿ� ����ġ�� �༭ ��뿡���� �Ȱ��� ��ġ��ŭ�� �̵��Ҽ��ֵ���
	RoomActor* FindRoom = RandomRoomManager::GetInst()->GetCurrentRoom();
	float4 AddPivot = FindRoom->GetPosition() - GameEngineWindow::GetScale().Half();

	// x���̳� y������ ���̻� ����������� x�� y�� �ѱ����� �����ϰ� �̵�
	float4 NextPos = GetPosition() + _Value;
	float4 NextPos_x = GetPosition() + float4(_Value.x, 0);
	float4 NextPos_y = GetPosition() + float4(0, _Value.y);
	int Color = MapColImage_->GetImagePixel(NextPos - AddPivot);
	int Color_x = MapColImage_->GetImagePixel(NextPos_x - AddPivot);
	int Color_y = MapColImage_->GetImagePixel(NextPos_y - AddPivot);

	if (
		RGB(0, 0, 0) != Color &&
		false == Collision_->NextPosCollisionCheckRect("Stone", _Value) &&
		false == Collision_->NextPosCollisionCheckRect("Wall", _Value) &&
		false == Collision_->NextPosCollisionCheckRect("Poop", _Value) &&
		false == Collision_->NextPosCollisionCheckRect("Hole", _Value)
		)
	{
		SetMove(_Value);
	}
	else if (
		RGB(0, 0, 0) != Color &&
		false == Collision_->NextPosCollisionCheckRect("Stone", float4(_Value.x, 0)) &&
		false == Collision_->NextPosCollisionCheckRect("Wall", float4(_Value.x, 0)) &&
		false == Collision_->NextPosCollisionCheckRect("Poop", float4(_Value.x, 0)) &&
		false == Collision_->NextPosCollisionCheckRect("Hole", float4(_Value.x, 0))
		)
	{
		SetMove(float4(_Value.x, 0));
	}
	else if (
		RGB(0, 0, 0) != Color &&
		false == Collision_->NextPosCollisionCheckRect("Stone", float4(0, _Value.y)) &&
		false == Collision_->NextPosCollisionCheckRect("Wall", float4(0, _Value.y)) &&
		false == Collision_->NextPosCollisionCheckRect("Poop", float4(0, _Value.y)) &&
		false == Collision_->NextPosCollisionCheckRect("Hole", float4(0, _Value.y))
		)
	{
		SetMove(float4(0, _Value.y));
	}
}

bool Monster::MonsterSetMoveToTeleport(float4 _Value)
{
	GameEngineImage* MapColImage_ = GameEngineImageManager::GetInst()->Find("basementTestCol.bmp");

	float4 AddPivot = Room_->GetPosition() - GameEngineWindow::GetScale().Half();
	float4 NextPos = _Value;
	int Color = MapColImage_->GetImagePixel(NextPos - AddPivot);

	float4 AddValue = _Value - GetPosition();
	if (
		RGB(0, 0, 0) != Color &&
		false == Collision_->NextPosCollisionCheckRect("Stone", _Value - GetPosition()) &&
		false == Collision_->NextPosCollisionCheckRect("Wall", _Value - GetPosition()) &&
		false == Collision_->NextPosCollisionCheckRect("Poop", _Value - GetPosition()) &&
		false == Collision_->NextPosCollisionCheckRect("Hole", _Value - GetPosition()) &&
		false == Collision_->NextPosCollisionCheckRect("Player", _Value - GetPosition())
		)
	{
		SetMove(_Value - GetPosition());
		return true;
	}

	return false;
}

bool Monster::MonsterSetMoveToFlyReturn(float4 _Value)
{
	GameEngineImage* MapColImage_ = GameEngineImageManager::GetInst()->Find("basementTestCol.bmp");

	// �븶�� ũ��� �����Ƿ� ����ġ�� �༭ ��뿡���� �Ȱ��� ��ġ��ŭ�� �̵��Ҽ��ֵ���
	RoomActor* FindRoom = RandomRoomManager::GetInst()->GetCurrentRoom();
	float4 AddPivot = FindRoom->GetPosition() - GameEngineWindow::GetScale().Half();

	// x���̳� y������ ���̻� ����������� x�� y�� �ѱ����� �����ϰ� �̵�
	float4 NextPos = GetPosition() + _Value;
	float4 NextPos_x = GetPosition() + float4(_Value.x, 0);
	float4 NextPos_y = GetPosition() + float4(0, _Value.y);
	int Color = MapColImage_->GetImagePixel(NextPos - AddPivot);
	int Color_x = MapColImage_->GetImagePixel(NextPos_x - AddPivot);
	int Color_y = MapColImage_->GetImagePixel(NextPos_y - AddPivot);
	if (RGB(0, 0, 0) != Color &&
		false == Collision_->NextPosCollisionCheckRect("Wall", _Value))
	{
		SetMove(_Value);
		
		if (_Value.Len2D() < 0.1f)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (RGB(0, 0, 0) != Color_x &&
		false == Collision_->NextPosCollisionCheckRect("Wall", _Value))
	{
		float4 TmpPos = float4(_Value.x, 0);
		SetMove(TmpPos);
		
		if (TmpPos.Len2D() < 0.1f)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (RGB(0, 0, 0) != Color_y &&
		false == Collision_->NextPosCollisionCheckRect("Wall", _Value))
	{
		float4 TmpPos = float4(0, _Value.y);
		SetMove(TmpPos);

		if (TmpPos.Len2D() < 0.1f)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool Monster::MonsterSetMoveToWalkReturn(float4 _Value)
{
	GameEngineImage* MapColImage_ = GameEngineImageManager::GetInst()->Find("basementTestCol.bmp");

	// �븶�� ũ��� �����Ƿ� ����ġ�� �༭ ��뿡���� �Ȱ��� ��ġ��ŭ�� �̵��Ҽ��ֵ���
	RoomActor* FindRoom = RandomRoomManager::GetInst()->GetCurrentRoom();
	float4 AddPivot = FindRoom->GetPosition() - GameEngineWindow::GetScale().Half();

	// x���̳� y������ ���̻� ����������� x�� y�� �ѱ����� �����ϰ� �̵�
	float4 NextPos = GetPosition() + _Value;
	float4 NextPos_x = GetPosition() + float4(_Value.x, 0);
	float4 NextPos_y = GetPosition() + float4(0, _Value.y);
	int Color = MapColImage_->GetImagePixel(NextPos - AddPivot);
	int Color_x = MapColImage_->GetImagePixel(NextPos_x - AddPivot);
	int Color_y = MapColImage_->GetImagePixel(NextPos_y - AddPivot);

	if (
		RGB(0, 0, 0) != Color &&
		false == Collision_->NextPosCollisionCheckRect("Stone", _Value) &&
		false == Collision_->NextPosCollisionCheckRect("Wall", _Value) &&
		false == Collision_->NextPosCollisionCheckRect("Poop", _Value) &&
		false == Collision_->NextPosCollisionCheckRect("Hole", _Value)
		)
	{
		SetMove(_Value);
		if (_Value.Len2D() < 0.1f)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (
		RGB(0, 0, 0) != Color &&
		false == Collision_->NextPosCollisionCheckRect("Stone", float4(_Value.x, 0)) &&
		false == Collision_->NextPosCollisionCheckRect("Wall", float4(_Value.x, 0)) &&
		false == Collision_->NextPosCollisionCheckRect("Poop", float4(_Value.x, 0)) &&
		false == Collision_->NextPosCollisionCheckRect("Hole", float4(_Value.x, 0))
		)
	{
		float4 TmpPos = float4(_Value.x, 0);
		SetMove(TmpPos);

		if (TmpPos.Len2D() < 0.1f)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (
		RGB(0, 0, 0) != Color &&
		false == Collision_->NextPosCollisionCheckRect("Stone", float4(0, _Value.y)) &&
		false == Collision_->NextPosCollisionCheckRect("Wall", float4(0, _Value.y)) &&
		false == Collision_->NextPosCollisionCheckRect("Poop", float4(0, _Value.y)) &&
		false == Collision_->NextPosCollisionCheckRect("Hole", float4(0, _Value.y))
		)
	{
		float4 TmpPos = float4(0, _Value.y);
		SetMove(TmpPos);

		if (TmpPos.Len2D() < 0.1f)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

void Monster::Damaged(float _Damage)
{
	if (IsInvincibility_ == true)
	{
		return;
	}

	HP_ -= _Damage;
	MonsterDamaged();

	if (HP_ <= 0)
	{
		std::string TmpName = "death burst small";
		TmpName += std::to_string(GameEngineRandom::MainRandom->RandomInt(1, 3)) + ".wav";
		GameEngineSound::SoundPlayOneShotWithVolume(TmpName, 0, 0.1f * Option_SFX);

		MonsterDeath();
		MakeRandomBlood(2, 5);
		if (Room_ != nullptr)
		{
			Room_->MinusMonsterCount();
		}
		Off();
	}
}

void Monster::Heal(float _Value)
{
	HP_ += _Value;

	if (HP_ >= MaxHP_)
	{
		HP_ = MaxHP_;
	}
}

void Monster::MakeRandomBlood(int _Min, int _Max)
{
	int RandomInt = GameEngineRandom::MainRandom->RandomInt(_Min, _Max);
	for (int i = 0; i < RandomInt; i++)
	{
		GetLevel()->CreateActor<RandomBlood>()->SetPosition(GetPosition());
	}
}

void Monster::MonsterDeath()
{
	Off();
}
