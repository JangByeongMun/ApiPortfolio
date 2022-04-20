#pragma once
#include <Windows.h>
#include <map>
#include <string>

// Ό³Έν :
class GameEngineInput
{
private:
	class GameEngineKey
	{
		friend GameEngineInput;

		bool Down_;  
		bool Press_; 
		bool Up_;    
		bool Free_;  
		
		float Time_;
		int Key_;    

		void Update(float _DeltaTime);
		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key_);
		}
		void Reset()
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}
	};

	friend class GameEngineWindow;

private:
	static GameEngineInput* Inst_;

public:
	static GameEngineInput* GetInst()
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

public:
	void Update(float _DeltaTime = 0.0f);
	void CreateKey(const std::string& _Name, int _Key);

	float GetTime(const std::string& _Name);
	bool IsDown(const std::string& _Name);
	bool IsUp(const std::string& _Name);
	bool IsPress(const std::string& _Name);
	bool IsFree(const std::string& _Name);
	bool IsKey(const std::string& _Name);

	inline int GetMouseWheel()
	{
		return CurWheelValue;
	}

protected:

private:
	std::map<std::string, GameEngineKey> AllInputKey_;
	int WheelValue;
	int CurWheelValue;

	GameEngineInput();
	~GameEngineInput();

	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;
};

