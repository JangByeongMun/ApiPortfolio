#include "GameEngineImageManager.h"
#include "GameEngineBase/GameEngineDebug.h"
#include "GameEngineImage.h"

GameEngineImageManager* GameEngineImageManager::inst_ = new GameEngineImageManager();


GameEngineImageManager::GameEngineImageManager() 
{
}

GameEngineImageManager::~GameEngineImageManager() 
{
	std::map<std::string, GameEngineImage*>::iterator beginIter = allRes.begin();
	std::map<std::string, GameEngineImage*>::iterator endIter = allRes.end();

	for (; beginIter != endIter; ++beginIter)
	{
		if (nullptr != beginIter->second)
		{
			delete beginIter->second;
			beginIter->second = nullptr;
		}
	}
}

GameEngineImage* GameEngineImageManager::Create(std::string _name, float4 _scale)
{
	if (allRes.end() != allRes.find(_name))
	{
		MsgBoxAssert("이미 존재하는 이름의 이미지를 만들려고 했습니다.");
		return nullptr;
	}

	GameEngineImage* newImage = new GameEngineImage();
	newImage->SetName(_name);
	if (false == newImage->Create(_scale))
	{
		delete newImage;
		newImage = nullptr;
		MsgBoxAssert((_name + " 이미지를 생성하는데 실패했습니다.").c_str());
		return nullptr;
	}
	allRes.insert(std::make_pair(_name, newImage));
	return newImage;
}

