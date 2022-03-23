#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"
#include "GameEngineFile.h"

GameEngineDirectory::GameEngineDirectory() 
{
	SetCurrentPath();
}

GameEngineDirectory::~GameEngineDirectory() 
{
}

void GameEngineDirectory::Move(const std::string& _name)
{
	std::filesystem::path tmpPath = path_;
	tmpPath.append(_name);
	
	if (false == std::filesystem::exists(tmpPath))
	{
		MsgBoxAssertString(_name + " directory is not exists");
		return;
	}

	path_ = tmpPath;
}

void GameEngineDirectory::MoveParent()
{
	path_ = path_.parent_path();
}

void GameEngineDirectory::MoveParent(const std::string& _name)
{
	while (false == IsRoot())
	{
		path_ = path_.parent_path();
		if (GetFileName() == _name)
		{
			break;
		}
	}
}

bool GameEngineDirectory::IsRoot()
{
	return path_ == path_.root_directory();
}


std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string& _ext)
{
	// ���� ��ġ iterator
	std::filesystem::directory_iterator DirIter(path_);

	// Ȯ���ڸ� �빮�ڷ� ��ȯ �� .�� �־��־����� �ƴ��� Ȯ��
	std::string ext = _ext;
	if (ext != "")
	{
		GameEngineString::ToUpper(ext);
		if (std::string::npos == ext.find("."))
		{
			ext = "." + ext;
		}
	}

	std::vector<GameEngineFile> Return;
	for (const std::filesystem::directory_entry& entry : DirIter)
	{
		if (true == entry.is_directory())
		{
			continue;
		}

		if (ext != "")
		{
			GameEnginePath NewPath = entry.path();
			std::string OtherExt = NewPath.GetExtension();
			GameEngineString::ToUpper(OtherExt);

			if (OtherExt != ext)
			{
				continue;
			}
		}

		Return.push_back(GameEngineFile(entry.path()));
	}

	return Return;
}

