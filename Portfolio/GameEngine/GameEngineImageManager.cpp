#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEnginePath.h>

GameEngineImageManager* GameEngineImageManager::inst_ = new GameEngineImageManager();


GameEngineImageManager::GameEngineImageManager() 
{
}

GameEngineImageManager::~GameEngineImageManager() 
{
	std::map<std::string, GameEngineImage*>::iterator startIter = allRes.begin();
	std::map<std::string, GameEngineImage*>::iterator endIter = allRes.end();

	for (; startIter != endIter; ++startIter)
	{
		if (nullptr != startIter->second)
		{
			delete startIter->second;
			startIter->second = nullptr;
		}
	}
}

GameEngineImage* GameEngineImageManager::Find(const std::string& _name)
{
	std::string engineName = GameEngineString::ToUpperReturn(_name);
	std::map<std::string, GameEngineImage*>::iterator findIter = allRes.find(engineName);
	if (allRes.end() == findIter)
	{
		return nullptr;
	}

	return findIter->second;
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _name, const float4& _scale)
{
	std::string engineName = GameEngineString::ToUpperReturn(_name);
	if (allRes.end() != allRes.find(engineName))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� ������� �߽��ϴ�.");
		return nullptr;
	}

	GameEngineImage* newImage = new GameEngineImage();
	newImage->SetName(engineName);
	if (false == newImage->Create(_scale))
	{
		delete newImage;
		newImage = nullptr;
		MsgBoxAssert((_name + " �̹����� �����ϴµ� �����߽��ϴ�.").c_str());
		return nullptr;
	}
	allRes.insert(std::make_pair(engineName, newImage));
	return newImage;
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _name, HDC _dc)
{
	std::string engineName = GameEngineString::ToUpperReturn(_name);
	if (allRes.end() != allRes.find(engineName))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� �� ������� �߽��ϴ�.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(engineName);

	if (false == NewImage->Create(_dc))
	{
		delete NewImage;
		MsgBoxAssert((_name + "�̹����� �����ϴµ� �����߽��ϴ�.").c_str());
		return nullptr;
	}

	allRes.insert(std::make_pair(engineName, NewImage));

	return NewImage;
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _path)
{
	GameEnginePath newPath = GameEnginePath(_path);
	return Load(_path, newPath.GetFileName());
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _path, const std::string& _name)
{
	std::string engineName = GameEngineString::ToUpperReturn(_name);
	if (allRes.end() != allRes.find(engineName))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� �� ������� �߽��ϴ�.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(engineName);

	if (false == NewImage->Load(_path))
	{
		delete NewImage;
		MsgBoxAssert((_name + "�̹����� �����ϴµ� �����߽��ϴ�.").c_str());
		return nullptr;
	}

	allRes.insert(std::make_pair(engineName, NewImage));

	return NewImage;
}

