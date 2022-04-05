#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEnginePath.h>

GameEngineImageManager* GameEngineImageManager::Inst_ = new GameEngineImageManager();


GameEngineImageManager::GameEngineImageManager() 
{
}

GameEngineImageManager::~GameEngineImageManager() 
{
	{
		std::map<std::string, GameEngineFolderImage*>::iterator StartIter = AllFolderRes_.begin();
		std::map<std::string, GameEngineFolderImage*>::iterator EndIter = AllFolderRes_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr != StartIter->second)
			{
				delete StartIter->second;
				StartIter->second = nullptr;
			}
		}
	}

	{
		std::map<std::string, GameEngineImage*>::iterator StartIter = AllRes_.begin();
		std::map<std::string, GameEngineImage*>::iterator EndIter = AllRes_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr != StartIter->second)
			{
				delete StartIter->second;
				StartIter->second = nullptr;
			}
		}
	}
}

GameEngineImage* GameEngineImageManager::Find(const std::string& _Name)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);
	std::map<std::string, GameEngineImage*>::iterator FindIter = AllRes_.find(EngineName);
	if (AllRes_.end() == FindIter)
	{
		return nullptr;
	}

	return FindIter->second;
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, const float4& _Scale)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);
	if (AllRes_.end() != AllRes_.find(EngineName))
	{
		MsgBoxAssert("이미 존재하는 이름의 이미지를 만들려고 했습니다.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(EngineName);
	if (false == NewImage->Create(_Scale))
	{
		delete NewImage;
		NewImage = nullptr;
		MsgBoxAssert((_Name + " 이미지를 생성하는데 실패했습니다.").c_str());
		return nullptr;
	}
	AllRes_.insert(std::make_pair(EngineName, NewImage));
	return NewImage;
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, HDC _DC)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);
	if (AllRes_.end() != AllRes_.find(EngineName))
	{
		MsgBoxAssert("이미 존재하는 이름의 이미지를 또 만들려고 했습니다.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(EngineName);

	if (false == NewImage->Create(_DC))
	{
		delete NewImage;
		NewImage = nullptr;
		MsgBoxAssert((_Name + "이미지를 생성하는데 실패했습니다.").c_str());
		return nullptr;
	}

	AllRes_.insert(std::make_pair(EngineName, NewImage));

	return NewImage;
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _Path)
{
	GameEnginePath NewPath = GameEnginePath(_Path);
	return Load(_Path, NewPath.GetFileName());
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _Path, const std::string& _Name)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);
	if (AllRes_.end() != AllRes_.find(EngineName))
	{
		MsgBoxAssert("이미 존재하는 이름의 이미지를 또 만들려고 했습니다.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(EngineName);

	if (false == NewImage->Load(_Path))
	{
		delete NewImage;
		NewImage = nullptr;
		MsgBoxAssert((_Name + "이미지를 생성하는데 실패했습니다.").c_str());
		return nullptr;
	}

	AllRes_.insert(std::make_pair(EngineName, NewImage));

	return NewImage;
}

GameEngineFolderImage* GameEngineImageManager::FolderImageFind(const std::string& _Name)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineFolderImage*>::iterator FindIter = AllFolderRes_.find(EngineName);

	if (AllFolderRes_.end() == FindIter)
	{
		// MsgBoxAssert("이미 존재하는 이름의 이미지를 또 만들려고 했습니다.");
		return nullptr;
	}

	return FindIter->second;
}

GameEngineFolderImage* GameEngineImageManager::FolderImageLoad(const std::string& _Path)
{
	GameEnginePath NewPath = GameEnginePath(_Path);
	return GameEngineImageManager::FolderImageLoad(_Path, NewPath.GetFileName());
}

GameEngineFolderImage* GameEngineImageManager::FolderImageLoad(const std::string& _Path, const std::string& _Name)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);
	if (AllFolderRes_.end() != AllFolderRes_.find(EngineName))
	{
		MsgBoxAssert("이미 존재하는 이름의 폴더 이미지를 또 만들려고 했습니다.");
		return nullptr;
	}

	GameEngineFolderImage* NewImage = new GameEngineFolderImage();
	NewImage->SetName(EngineName);

	if (false == NewImage->Load(_Path))
	{
		delete NewImage;
		MsgBoxAssert((_Name + "이미지를 생성하는데 실패했습니다.").c_str());
		return nullptr;
	}

	AllFolderRes_.insert(std::make_pair(EngineName, NewImage));

	return NewImage;
}

