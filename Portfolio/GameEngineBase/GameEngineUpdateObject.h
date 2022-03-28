#pragma once
#include <string>
#include "GameEngineTime.h"

// Ό³Έν :
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
		if (false == isReleaseUpdate_)
		{
			return;
		}

		deathTime_ -= GameEngineTime::GetDeltaTime();

		if (0.0f >= deathTime_)
		{
			isDeath_ = true;
		}
	}

	inline void On()
	{
		isUpdate_ = true;
	}
	inline void Off()
	{
		isUpdate_ = false;
	}
	virtual bool IsUpdate()
	{
		return isUpdate_ && false == isDeath_;
	}

	inline void Death()
	{
		isDeath_ = true;
	}
	inline void Death(float _Time)
	{
		isReleaseUpdate_ = true;
		deathTime_ = _Time;
	}
	inline bool IsDeath()
	{
		return isDeath_;
	}

protected:

private:
	bool isReleaseUpdate_;
	bool isUpdate_;
	
	float deathTime_;
	bool isDeath_;
};

