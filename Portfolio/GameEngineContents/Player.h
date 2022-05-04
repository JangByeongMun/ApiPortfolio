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
	TrapDoor,
};
enum class PlayerHeadState
{
	Idle,
	Attack,
	Move,
	Acheive,
	Hitted,
	Dead,
	TrapDoor,
};

// 설명 : 플레이어
class GameEngineImage;
class PlayerUI;
class PlayerHP;
class ActiveUI;
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
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	void PlayerSetMove(const float4& _Value);
	bool CanMove(const float4& _Value);

///////////////////////////////// FSM
private:
	PlayerBodyState CurBody_;
	PlayerHeadState CurHead_;
	float4 MoveDir_;
	bool IsDead_;

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
	void BodyTrapdoorStart();

	// Head Start
	void HeadIdleStart();
	void HeadAttackStart();
	void HeadMoveStart();
	void HeadAcheiveStart(); 
	void HeadHittedStart();
	void HeadDeadStart();
	void HeadTrapdoorStart();

	// Body Update
	void BodyIdleUpdate();
	void BodyMoveUpdate();
	void BodyAcheiveUpdate();
	void BodyHittedUpdate();
	void BodyDeadUpdate();
	void BodyTrapdoorUpdate();

	// Head Update
	void HeadIdleUpdate();
	void HeadAttackUpdate();
	void HeadMoveUpdate();
	void HeadAcheiveUpdate();
	void HeadHittedUpdate();
	void HeadDeadUpdate();
	void HeadTrapdoorUpdate();


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

public:
	inline float GetDamage()
	{
		return Damage_ + AddDamageTo109_;
	}
	inline float GetAttackSpeed()
	{
		return AttackSpeed_;
	}
	inline float GetRange()
	{
		return Range_;
	}
	inline float GetShotSpeed()
	{
		return ShotSpeed_;
	}
	inline float GetMoveSpeed()
	{
		return MoveSpeed_;
	}
	inline float GetLuck()
	{
		return Luck_;
	}

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
	inline int GetMoney()
	{
		return MoneyCount_;
	}
	void BlackHeartDestroy();

///////////////////////////////// UI 통괄
private:
	PlayerUI* PlayerUI_;

public:
	inline PlayerUI* GetPlayerUI()
	{
		return PlayerUI_;
	}
	PlayerHP* GetPlayerHP();
	ActiveUI* GetActiveUI();

///////////////////////////////// 악세사리
private:
	AccessoryType HavingAccessory_;

public:
	void SetAccessory(AccessoryType _Type);

///////////////////////////////// 액티브 아이템
private:
	ActiveType ActiveType_;
	int MaxGaze_;
	int CurrentGaze_;
	bool IsUsingActive;

public:
	inline bool IsActiveOn()
	{
		return MaxGaze_ <= CurrentGaze_;
	}
	inline void SetActiveType(ActiveType _Type)
	{
		ActiveType_ = _Type;
		switch (_Type)
		{
		case ActiveType::Default:
			break;
		case ActiveType::Item034:
			MaxGaze_ = 3;
			break;
		case ActiveType::Item036:
			MaxGaze_ = 1;
			break;
		case ActiveType::Item045:
			MaxGaze_ = 4;
			break;
		case ActiveType::Max:
			break;
		default:
			break;
		}
		CurrentGaze_ = 0;
	}
	inline ActiveType GetActiveType()
	{
		return ActiveType_;
	}
	void SetGaze(int _Value);
	void AddGaze(int _Value);
	
	void UseActive();

///////////////////////////////// 패시브 아이템
private:
	std::vector<PassiveType> PassiveVector_;
	bool Have109_;
	bool Have245_;
	bool Have246_;
	bool Have302_;

	float AddDamageTo109_;

public:
	void AddPassive(PassiveType _Type);
	void AddPassiveEffect(PassiveType _Type);
	void MakeItemRenderer(PassiveType _Type);
	bool IsAlreadyHave(PassiveType _Type);

	void EffectItem001();
	void EffectItem015();
	void EffectItem072();
	void EffectItemDefault(PassiveType _Type);

	inline bool Have109()
	{
		return Have109_;
	}
	inline bool Have245()
	{
		return Have245_;
	}
	inline bool Have246()
	{
		return Have246_;
	}
	inline bool Have302()
	{
		return Have302_;
	}

///////////////////////////////// 방
private:
	float4 RoomPos_;

public:	
	void SetRoom(float4 _Pos);
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

