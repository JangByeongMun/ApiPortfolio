#pragma once
#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineMath.h>
#include <map>

// Ό³Έν :
class GameEngineImageManager
{
private:
	static GameEngineImageManager* inst_;
public:
	inline static GameEngineImageManager* GetInst() 
	{
		return inst_;
	}
	
	inline static void Destroy()
	{
		if (nullptr == inst_)
		{
			return;
		}

		delete inst_;
		inst_ = nullptr;
	}

public:
	// constrcuter destructer
	GameEngineImageManager();
	~GameEngineImageManager();

	// delete Function
	GameEngineImageManager(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager(GameEngineImageManager&& _Other) noexcept = delete;
	GameEngineImageManager& operator=(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager& operator=(GameEngineImageManager&& _Other) noexcept = delete;

	GameEngineImage* Create(std::string _name, float4 _scale);

protected:

private:
	std::map<std::string, GameEngineImage*> allRes;
};

