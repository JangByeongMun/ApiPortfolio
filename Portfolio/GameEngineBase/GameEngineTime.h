#pragma once
#include <map>

// 설명 :
class GameEngineTime
{
private:
	static GameEngineTime* Inst_;

public:
	static GameEngineTime* GetInst()
	{
		return Inst_;
	}
	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

	// 전체 정지일때도 움직일수 있는 것들 구현을 위한것
	static inline float GetUnstoppableDeltaTime()
	{
		return Inst_->DeltaTime_;
	}
	static inline float GetDeltaTime()
	{
		if (true == IsPause_)
		{
			return 0.0f;
		}

		return Inst_->DeltaTime_;
	}
	static inline float GetDeltaTime(int _Key)
	{
		if (true == IsPause_)
		{
			return 0.0f;
		}

		return Inst_->DeltaTime_ * Inst_->GetTimeScale(_Key);
	}

	void SetTimeScale(int _Key, float _TimeScale)
	{
		if (TimeScale_.end() == TimeScale_.find(_Key))
		{
			_TimeScale = 1.0f;
		}

		TimeScale_[_Key] = _TimeScale;
	}
	float GetTimeScale(int _Key)
	{
		if (TimeScale_.end() == TimeScale_.find(_Key))
		{
			TimeScale_[_Key] = 1.0f;
		}

		return TimeScale_[_Key];
	}

	void Reset();
	void Update();

	static inline void Pause()
	{
		IsPause_ = !IsPause_;
	}
	static inline bool IsPause()
	{
		return IsPause_;
	}
protected:

private:
	__int64 SecondCount_;
	__int64 CurrentCount_;
	__int64 PrevCount_;
	float DeltaTime_;
	double RealDeltaTime_;
	std::map<int, float> TimeScale_;
	static bool IsPause_;

	GameEngineTime();
	~GameEngineTime();
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;
};
 
