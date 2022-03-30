#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <map>
#include <string>
#include "GameEngineImage.h"

// Ό³Έν :
class GameEngineImageManager
{
private:
	static GameEngineImageManager* Inst_;
public:
	inline static GameEngineImageManager* GetInst() 
	{
		return Inst_;
	}
	
	inline static void Destroy()
	{
		if (nullptr == Inst_)
		{
			return;
		}

		delete Inst_;
		Inst_ = nullptr;
	}

public:
	GameEngineImage* Find(const std::string& _Name);
	GameEngineImage* Create(const std::string& _Name, const float4& _Scale);
	GameEngineImage* Create(const std::string& _Name, HDC _DC);
	GameEngineImage* Load(const std::string& _Path);
	GameEngineImage* Load(const std::string& _Path, const std::string& _Name);

protected:

private:
	std::map<std::string, GameEngineImage*> AllRes;

	GameEngineImageManager();
	~GameEngineImageManager();

	GameEngineImageManager(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager(GameEngineImageManager&& _Other) noexcept = delete;
	GameEngineImageManager& operator=(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager& operator=(GameEngineImageManager&& _Other) noexcept = delete;
};

