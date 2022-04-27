#pragma once
#include <string>
#include "GameEngineTime.h"

// 설명 :
class GameEngineUpdateObject
{
public:
	// constrcuter destructer
	GameEngineUpdateObject();
	~GameEngineUpdateObject();

	// delete Function
	GameEngineUpdateObject(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject(GameEngineUpdateObject&& _Other) noexcept = delete;
	GameEngineUpdateObject& operator=(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject& operator=(GameEngineUpdateObject&& _Other) noexcept = delete;

	inline void ReleaseUpdate()
	{
		if (false == IsReleaseUpdate_)
		{
			return;
		}

		DeathTime_ -= GameEngineTime::GetDeltaTime();
		if (0.0f >= DeathTime_ && true == IsDeathStart_)
		{
			IsDeath_ = true;
			IsReleaseUpdate_ = false;
		}

		OnTime_ -= GameEngineTime::GetDeltaTime();
		if (0.0f >= OnTime_ && true == IsOnStart_)
		{
			IsUpdate_ = true;
			IsOnStart_ = false;
			IsReleaseUpdate_ = false;
		}
	}

	inline void On()
	{
		IsUpdate_ = true;
	}
	inline void On(float _Time)
	{
		IsOnStart_ = true;
		IsReleaseUpdate_ = true;
		OnTime_ = _Time;
	}

	inline void Off()
	{
		IsUpdate_ = false;
	}
	inline virtual bool IsUpdate()
	{
		return IsUpdate_ && false == IsDeath_;
	}

	inline void Death()
	{
		IsDeath_ = true;
	}
	inline void Death(float _Time)
	{
		IsDeathStart_ = true;
		IsReleaseUpdate_ = true;
		DeathTime_ = _Time;
	}
	inline virtual bool IsDeath()
	{
		return IsDeath_;
	}

	inline int GetOrder()
	{
		return Order_;
	}
	virtual inline void SetOrder(int _Order)
	{
		Order_ = _Order;
	}


	void AddAccTime(float _DeltaTime)
	{
		AccTime_ += _DeltaTime;
	}

	float GetAccTime()
	{
		return AccTime_;
	}


	void ReSetAccTime()
	{
		AccTime_ = 0.0f;
	}


protected:

private:
	int Order_;
	bool IsReleaseUpdate_;
	bool IsUpdate_;
	float AccTime_;

	float DeathTime_;
	bool IsDeath_;
	
	// 죽는거말고 켜지는것도 시간제한 둘려고 죽는게 켜졌을때를 확인하는기능을 따로 만듬
	bool IsDeathStart_;
	
	float OnTime_;
	bool IsOnStart_;
};

