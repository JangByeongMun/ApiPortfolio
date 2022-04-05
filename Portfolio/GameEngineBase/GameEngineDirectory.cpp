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
		MsgBoxAssert("�������� �ʴ� ������ �ʱ�ȭ�Ϸ��� �߽��ϴ�.")
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

// Ȯ���ڸ��� �޾Ƽ� ������ġ�� �ش� Ȯ���ڸ� ���� ���ϵ� ���� ���������Լ�
std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string& _Ext)
{
	// ���� ��ġ iterator
	std::filesystem::directory_iterator DirIter(Path_);

	// Ȯ���ڸ� �빮�ڷ� ��ȯ �� .�� �־��־����� �ƴ��� Ȯ��
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

