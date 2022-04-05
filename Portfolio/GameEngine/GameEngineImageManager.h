#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <map>

#include "GameEngineImage.h"
#include "GameEngineFolderImage.h"

// 설명 :
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

private:
	GameEngineImageManager();
	~GameEngineImageManager();

	GameEngineImageManager(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager(GameEngineImageManager&& _Other) noexcept = delete;
	GameEngineImageManager& operator=(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager& operator=(GameEngineImageManager&& _Other) noexcept = delete;

	/////////////// 일반이미지
private:
	std::map<std::string, GameEngineImage*> AllRes_;

public:
	GameEngineImage* Find(const std::string& _Name);
	GameEngineImage* Create(const std::string& _Name, const float4& _Scale);
	GameEngineImage* Create(const std::string& _Name, HDC _DC);
	GameEngineImage* Load(const std::string& _Path);
	GameEngineImage* Load(const std::string& _Path, const std::string& _Name);


	/////////////// 폴더이미지
private:
	std::map<std::string, GameEngineFolderImage*> AllFolderRes_;

public:
	GameEngineFolderImage* FolderImageFind(const std::string& _Name);
	GameEngineFolderImage* FolderImageLoad(const std::string& _Path);
	GameEngineFolderImage* FolderImageLoad(const std::string& _Path, const std::string& _Name);
};

