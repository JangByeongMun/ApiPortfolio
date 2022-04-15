#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Shooter.h"
#include <vector>

enum class PlayerBodyState
{
	None,
	Idle,
	Move
};

enum class PlayerHeadState
{
	None,
	Idle,
	Attack,
	Move,
};

// 설명 : 플레이어
class GameEngineImage;
class PlayerUI;
class Player : public Shooter
{
	friend PlayerUI;
public:
	static Player* MainPlayer;
	
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void GetPlayerInfo();
	void MakeHeadAddRenderer(const std::string& _Name);

	std::string GetBodyAnimationName();
	std::string GetHeadAnimationName();

protected:
	
private:
	GameEngineRenderer* BodyRender_;
	GameEngineRenderer* HeadRender_;
	std::vector<GameEngineRenderer*> HeadAddRender_;
	GameEngineCollision* PlayerCollision;
	GameEngineImage* MapColImage_;

	std::string BodyAnimationName;
	std::string HeadAnimationName;
	std::string BlueBodyAnimationName;
	std::string BlueHeadAnimationName;

	void Start() override;
	void Update() override;
	void LevelChangeStart() override;

	void CollisionCheck();
	void PlayerSetMove(float4 _Value);

///////////////////////////////// FSM
private:
	PlayerBodyState CurBody_;
	PlayerHeadState CurHead_;
	float4 MoveDir_;

	bool IsMoveKey();
	bool IsAttackKey();

public:
	void ChangeBodyState(PlayerBodyState _State);
	void ChangeHeadState(PlayerHeadState _State);
	void StateUpdate();

private: 
	void BodyIdleStart();
	void BodyMoveStart();
	void HeadIdleStart();
	void HeadAttackStart();
	void HeadMoveStart();

	void BodyIdleUpdate();
	void BodyMoveUpdate();
	void HeadIdleUpdate();
	void HeadAttackUpdate();
	void HeadMoveUpdate();

///////////////////////////////// 기본정보
private:
	int MaxHp_;
	float Damage_;
	float AttackSpeed_;
	float ShotSpeed_;
	float Range_;
	float MoveSpeed_;
	float Luck_;

///////////////////////////////// 공격속도
private:
	float NextAttackTime_;
	float CurrentAttackTime_;

///////////////////////////////// 좌상단 플레이어정보
private:
	int MoneyCount_;
	int KeyCount_;
	int BombCount_;
	bool IsMasterKey_;

public:
	void AddItem(ItemType _Type);

///////////////////////////////// UI 통괄
private:
	PlayerUI* PlayerUI_;


///////////////////////////////// 악세사리
private:
	AccessoryType HavingAccessory_;

public:
	void SetAccessory(AccessoryType _Type);
};

