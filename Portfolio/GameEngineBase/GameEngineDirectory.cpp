#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"
#include "GameEngineFile.h"

GameEngineDirectory::GameEngineDirectory() 
{
	SetCurrentPath();
}

GameEngineDirectory::GameEngineDirectory(const std::string& _Path)
{
	Path_ = _Path;
	if (false == IsExists())
	{
		MsgBoxAssert("존재하지 않는 폴더로 초기화하려고 했습니다.")
	}
}

GameEngineDirectory::~GameEngineDirectory() 
{
}

void GameEngineDirectory::Move(const std::string& _Name)
{
	std::filesystem::path CheckPath = Path_;
	CheckPath.append(_Name);
	
	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssertString(_Name + " Path is not exists");
		return;
	}

	Path_ = CheckPath;
}

void GameEngineDirectory::MoveParent()
{
	Path_ = Path_.parent_path();
}

void GameEngineDirectory::MoveParent(const std::string& _Name)
{
	while (false == IsRoot())
	{
		Path_ = Path_.parent_path();
		if (GetFileName() == _Name)
		{
			break;
		}
	}
}

bool GameEngineDirectory::IsRoot()
{
	return Path_ == Path_.root_directory();
}

// 확장자명을 받아서 현재위치의 해당 확장자를 가진 파일들 전부 가져오는함수
std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string& _Ext)
{
	// 현재 위치 iterator
	std::filesystem::directory_iterator DirIter(Path_);

	// 확장자를 대문자로 변환 및 .을 넣어주었는지 아닌지 확인
	std::string Ext = _Ext;
	if (Ext != "")
	{
		GameEngineString::ToUpper(Ext);
		if (std::string::npos == Ext.find("."))
		{
			Ext = "." + Ext;
		}
	}

	std::vector<GameEngineFile> Return;
	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		if (true == Entry.is_directory())
		{
			continue;
		}

		if (Ext != "")
		{
			GameEnginePath NewPath = Entry.path();
			std::string OtherExt = NewPath.GetExtension();
			GameEngineString::ToUpper(OtherExt);

			if (OtherExt != Ext)
			{
				continue;
			}
		}

		Return.push_back(GameEngineFile(Entry.path()));
	}

	return Return;
}

