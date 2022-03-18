#include "GameEngineImageManager.h"
#include "GameEngineBase/GameEngineDebug.h"

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
		MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� ������� �߽��ϴ�.");
		return nullptr;
	}

	GameEngineImage* newImage = new GameEngineImage();
	newImage->SetName(_name);
	if (false == newImage->Create(_scale))
	{
		delete newImage;
		newImage = nullptr;
		MsgBoxAssert((_name + " �̹����� �����ϴµ� �����߽��ϴ�.").c_str());
		return nullptr;
	}
	allRes.insert(std::make_pair(_name, newImage));
	return newImage;
}

GameEngineImage* GameEngineImageManager::Create(std::string _name, HDC _dc)
{
	if (allRes.end() != allRes.find(_name))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� �� ������� �߽��ϴ�.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(_name);

	if (false == NewImage->Create(_dc))
	{
		delete NewImage;
		MsgBoxAssert((_name + "�̹����� �����ϴµ� �����߽��ϴ�.").c_str());
		return nullptr;
	}

	allRes.insert(std::make_pair(_name, NewImage));

	return NewImage;
}

