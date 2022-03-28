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
		int Key_;    

		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key_);
		}
		void Update()
		{
			if (true == KeyCheck())
			{
				int a = 0;
				if (true == Free_)
				{
					Down_ = true;
					Press_ = true;
					Up_ = false;
					Free_ = false;
				}
				else if (true == Press_)
				{
					Down_ = false;
					Press_ = true;
					Up_ = false;
					Free_ = false;
				}
			}
			else
			{
				if (true == Press_)
				{
					Down_ = false;
					Press_ = false;
					Up_ = true;
					Free_ = false;
				}
				else if (true == Up_)
				{
					Down_ = false;
					Press_ = false;
					Up_ = false;
					Free_ = true;
				}
			}
		}
		void Reset()
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}
	};

private:
	static GameEngineInput* inst_;

public:
	static GameEngineInput* GetInst();
	static void Destroy()
	{
		if (nullptr != inst_)
		{
			delete inst_;
			inst_ = nullptr;
		}
	}

	void Update();

	void CreateKey(const std::string& _name, int _key);
	bool IsDown(const std::string& _name);
	bool IsUp(const std::string& _name);
	bool IsPress(const std::string& _name);
	bool IsFree(const std::string& _name);
	bool IsKey(const std::string& _name);

protected:

private:
	GameEngineInput();
	~GameEngineInput();
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;
	
	std::map<std::string, GameEngineKey> allInputKey_;
};

