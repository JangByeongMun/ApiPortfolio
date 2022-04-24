#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Shooter.h"
#include <vector>
#include <string>

enum class PlayerBodyState
{
	Idle,
	Move,
	Acheive,
	Hitted,
	Dead,
};
enum class PlayerHeadState
{
	Idle,
	Attack,
	Move,
	Acheive,
	Hitted,
	Dead,
};

// 설명 : 플레이어
class GameEngineImage;
class PlayerUI;
class PlayerHP;
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

	void SetPlayerInfo();
	void MakeHeadAddRenderer(const std::string& _Name);

	std::string GetBodyAnimationName();
	std::string GetHeadAnimationName();

	inline GameEngineImage* GetMapColImage()
	{
		return MapColImage_;
	}

protected:
	
private:
	std::vector<GameEngineRenderer*> AnimRender_;
	GameEngineRenderer* AcheiveItemRender_; // 먹은 아이템 보여주는 렌더러

	GameEngineRenderer* BodyRender_;
	GameEngineRenderer* HeadRender_;
	std::vector<GameEngineRenderer*> HeadAddRender_;
	GameEngineCollision* PlayerCollision_;
	GameEngineImage* MapColImage_;

	std::string BodyAnimationName;
	std::string HeadAnimationName;
	std::string BlueBodyAnimationName;
	std::string BlueHeadAnimationName;

	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	void PlayerSetMove(const float4& _Value);
	bool CanMove(const float4& _Value);

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
	void SetAcheiveRenderer(const std::string& _Name);

private: 
	// Body Start
	void BodyIdleStart();
	void BodyMoveStart();
	void BodyAcheiveStart();
	void BodyHittedStart();
	void BodyDeadStart();

	// Head Start
	void HeadIdleStart();
	void HeadAttackStart();
	void HeadMoveStart();
	void HeadAcheiveStart(); 
	void HeadHittedStart();
	void HeadDeadStart();

	// Body Update
	void BodyIdleUpdate();
	void BodyMoveUpdate();
	void BodyAcheiveUpdate();
	void BodyHittedUpdate();
	void BodyDeadUpdate();

	// Head Update
	void HeadIdleUpdate();
	void HeadAttackUpdate();
	void HeadMoveUpdate();
	void HeadAcheiveUpdate();
	void HeadHittedUpdate();
	void HeadDeadUpdate();


///////////////////////////////// 기본정보
private:
	CharacterType CharacterType_;
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
	bool MinusItem(ItemType _Type, int _Value);
	inline bool HaveKey()
	{
		return KeyCount_ >= 1 || true == IsMasterKey_;
	}

///////////////////////////////// UI 통괄
private:
	PlayerUI* PlayerUI_;

public:
	inline PlayerUI* GetPlayerUI()
	{
		return PlayerUI_;
	}
	PlayerHP* GetPlayerHP();

///////////////////////////////// 악세사리
private:
	AccessoryType HavingAccessory_;

public:
	void SetAccessory(AccessoryType _Type);

///////////////////////////////// 액티브 아이템
private:
	bool HaveActive_;
	int MaxGaze_;
	int CurrentGaze_;

public:
	inline bool IsActiveOn()
	{
		return MaxGaze_ <= CurrentGaze_;
	}
	void SetActive();

///////////////////////////////// 패시브 아이템
private:
	std::vector<PassiveType> PassiveVector_;

public:
	inline void AddPassive(PassiveType _Type)
	{
		std::string TmpName = "collectibles_";
		int TypeInt = static_cast<int>(_Type);
		if (TypeInt >= 100)
		{
			TmpName += std::to_string(TypeInt);
		}
		else if (TypeInt >= 10)
		{
			TmpName += "0" + std::to_string(TypeInt);
		}
		else
		{
			TmpName += "00" + std::to_string(TypeInt);
		}
		TmpName += ".bmp";

		AddPassiveEffect(_Type);

		PassiveVector_.push_back(_Type);
		ChangeBodyState(PlayerBodyState::Acheive);
		ChangeHeadState(PlayerHeadState::Acheive);
		SetAcheiveRenderer(TmpName);
	}
	inline void AddPassiveEffect(PassiveType _Type)
	{
		switch (_Type)
		{
		case PassiveType::Default:
			break;
		case PassiveType::Item1:
			AttackSpeed_ += 0.7f;
			break;
		case PassiveType::Max:
			break;
		default:
			break;
		}
	}

///////////////////////////////// 방
private:
	float4 RoomPos_;

public:	
	void ChangeRoom(DoorDir _Value);
	inline float4 GetCurrentRoomPos()
	{
		return RoomPos_;
	}

///////////////////////////////// 무적시간
private:
	float InvincibilityTimer_;
	float InvisibleTimer_;

public:
	bool IsInvincibillity()
	{
		return InvincibilityTimer_ > 0.0f;
	}

};

