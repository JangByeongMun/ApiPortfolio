#pragma once

// Ό³Έν :
class GameEngineTime
{
private:
	static GameEngineTime* inst_;

public:
	static GameEngineTime* GetInst()
	{
		return inst_;
	}
	static void Destroy()
	{
		if (nullptr != inst_)
		{
			delete inst_;
			inst_ = nullptr;
		}
	}

public:
	void Reset();
	void Update();

	inline float GetDeltaTime()
	{
		return deltaTime_;
	}

protected:

private:
	__int64 secondCount_;
	__int64 currentCount_;
	__int64 prevCount_;
	float deltaTime_;
	double realDeltaTime_;

	GameEngineTime();
	~GameEngineTime();
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;
};

