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

GameEngineImage* GameEngineImageManager::Find(const std::string& _name)
{
	std::map<std::string, GameEngineImage*>::iterator findIter = allRes.find(_name);
	if (allRes.end() == findIter)
	{
		return nullptr;
	}

	return findIter->second;
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _name, const float4& _scale)
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

GameEngineImage* GameEngineImageManager::Create(const std::string& _name, HDC _dc)
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

GameEngineImage* GameEngineImageManager::Load(const std::string& _path)
{
	return nullptr;
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _path, const std::string& _name)
{
	if (allRes.end() != allRes.find(_name))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� �� ������� �߽��ϴ�.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(_name);

	if (false == NewImage->Load(_path))
	{
		delete NewImage;
		MsgBoxAssert((_name + "�̹����� �����ϴµ� �����߽��ϴ�.").c_str());
		return nullptr;
	}

	allRes.insert(std::make_pair(_name, NewImage));

	return NewImage;
}

