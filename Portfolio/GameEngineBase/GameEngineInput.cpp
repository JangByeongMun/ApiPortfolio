#include "GameEngineInput.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

//////////////////////////////////////////////////
void GameEngineInput::GameEngineKey::Update()
{
	if (true == KeyCheck())
	{
		if (true == Free_)
		{
			Down_ = true;
			Press_ = true;
			Up_ = false;
			Free_ = false;
		}
		else if (true == Press_)
		{
			Down_ = false;
			Press_ = true;
			Up_ = false;
			Free_ = false;
		}
	}
	else
	{
		if (true == Press_)
		{
			Down_ = false;
			Press_ = false;
			Up_ = true;
			Free_ = false;
		}
		else if (true == Up_)
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}
	}
}
//////////////////////////////////////////////////


GameEngineInput* GameEngineInput::Inst_ = new GameEngineInput();

GameEngineInput::GameEngineInput() 
{
}

GameEngineInput::~GameEngineInput() 
{
}

GameEngineInput* GameEngineInput::GetInst()
{
	return Inst_;
}

void GameEngineInput::Update()
{
	std::map<std::string, GameEngineKey>::iterator keyUpdateStart = AllInputKey_.begin();
	std::map<std::string, GameEngineKey>::iterator keyUpdateEnd = AllInputKey_.end();
	
	for (; keyUpdateStart != keyUpdateEnd; ++keyUpdateStart)
	{
		keyUpdateStart->second.Update();
	}
}

void GameEngineInput::CreateKey(const std::string& _Name, int _Key)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	if (AllInputKey_.end() != AllInputKey_.find(UpperName))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� Ű�� �� ������� �߽��ϴ�");
		return;
	}

	if ('a' <= _Key && _Key <= 'z')
	{
		_Key = std::toupper(_Key);
	}

	AllInputKey_.insert(std::make_pair(UpperName, GameEngineKey()));
	AllInputKey_[UpperName].Key_ = _Key;
	AllInputKey_[UpperName].Reset();
}

bool GameEngineInput::IsDown(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	if (AllInputKey_.end() == AllInputKey_.find(UpperName))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}
	return AllInputKey_[UpperName].Down_;
}

bool GameEngineInput::IsUp(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	if (AllInputKey_.end() == AllInputKey_.find(UpperName))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}
	return AllInputKey_[UpperName].Up_;
}

bool GameEngineInput::IsPress(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	if (AllInputKey_.end() == AllInputKey_.find(UpperName))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}
	return AllInputKey_[UpperName].Press_;
}

bool GameEngineInput::IsFree(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	if (AllInputKey_.end() == AllInputKey_.find(UpperName))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}
	return AllInputKey_[UpperName].Free_;
}

bool GameEngineInput::IsKey(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	return AllInputKey_.end() != AllInputKey_.find(UpperName);
}


