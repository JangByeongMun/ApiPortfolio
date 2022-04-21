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

Monster::Monster()
	: Room_(nullptr)
	, Renderer_(nullptr)
	, Collision_(nullptr)
	, IsLeft_(true)
	, AttackTimer_(0.0f)
	, AttackDelay_(5.0f)
	, MoveSpeed_(100.0f)
	, HP_(0)
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
	// 현재 방에 있는 몬스터들만 상태 변경하도록 다른방일땐 return;
	if (false == Room_->IsCurrentRoom())
	{
		return;
	}

	IsLeft_ = AttackNormalDir().x <= 0;
	MonsterUpdate();
}

///////////////////////////////// 공격
float4 Monster::AttackNormalDir()
{
	float4 ReturnFloat4 = Player::MainPlayer->GetPosition() - GetPosition();
	ReturnFloat4.Normal2D();
	return ReturnFloat4;
}

///////////////////////////////// 이동
void Monster::MonsterSetMove(float4 _Value)
{
	GameEngineImage* MapColImage_ = GameEngineImageManager::GetInst()->Find("basementTestCol.bmp");

	// 룸마다 크기는 같으므로 보정치를 줘서 어떤룸에서도 똑같은 위치만큼만 이동할수있도록
	RoomActor* FindRoom = RandomRoomManager::GetInst()->GetCurrentRoom();
	float4 AddPivot = FindRoom->GetPosition() - GameEngineWindow::GetScale().Half();

	// x축이나 y축으로 더이상 갈수없을경우 x나 y중 한군데를 제외하고 이동
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

void Monster::Damaged(float _Damage)
{
	HP_ -= _Damage;

	if (HP_ <= 0)
	{
		Room_->MinusMonsterCount();
		MonsterDeath();
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
	Death();
}
