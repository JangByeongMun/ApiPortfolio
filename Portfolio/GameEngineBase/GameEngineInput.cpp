#include "GameEngineInput.h"
#include "GameEngineDebug.h"

GameEngineInput* GameEngineInput::inst_ = new GameEngineInput();

GameEngineInput::GameEngineInput() 
{
}

GameEngineInput::~GameEngineInput() 
{
}

GameEngineInput* GameEngineInput::GetInst()
{
	return inst_;
}

void GameEngineInput::Update()
{
	std::map<std::string, GameEngineKey>::iterator keyUpdateStart = allInputKey_.begin();
	std::map<std::string, GameEngineKey>::iterator keyUpdateEnd = allInputKey_.end();
	
	for (; keyUpdateStart != keyUpdateEnd; ++keyUpdateStart)
	{
		keyUpdateStart->second.Update();
	}
}

void GameEngineInput::CreateKey(std::string _name, int _key)
{
	if (allInputKey_.end() != allInputKey_.find(_name))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� Ű�� �� ������� �߽��ϴ�");
		return;
	}

	if ('a' <= _key && _key <= 'z')
	{
		_key = std::toupper(_key);
	}

	allInputKey_.insert(std::make_pair(_name, GameEngineKey()));
	allInputKey_[_name].Key_ = _key;
	allInputKey_[_name].Reset();
}

bool GameEngineInput::IsDown(std::string _name)
{
	if (allInputKey_.end() == allInputKey_.find(_name))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}
	return allInputKey_[_name].Down_;
}

bool GameEngineInput::IsUp(std::string _name)
{
	if (allInputKey_.end() == allInputKey_.find(_name))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}
	return allInputKey_[_name].Up_;
}

bool GameEngineInput::IsPress(std::string _name)
{
	if (allInputKey_.end() == allInputKey_.find(_name))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}
	return allInputKey_[_name].Press_;
}

bool GameEngineInput::IsFree(std::string _name)
{
	if (allInputKey_.end() == allInputKey_.find(_name))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}
	return allInputKey_[_name].Free_;
}

bool GameEngineInput::IsKey(std::string _name)
{
	return allInputKey_.end() != allInputKey_.find(_name);
}


