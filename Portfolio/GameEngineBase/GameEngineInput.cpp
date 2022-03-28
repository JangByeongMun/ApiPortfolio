#include "GameEngineInput.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

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

void GameEngineInput::CreateKey(const std::string& _name, int _key)
{
	std::string upperName = GameEngineString::ToUpperReturn(_name);
	if (allInputKey_.end() != allInputKey_.find(upperName))
	{
		MsgBoxAssert("이미 존재하는 이름의 키를 또 만들려고 했습니다");
		return;
	}

	if ('a' <= _key && _key <= 'z')
	{
		_key = std::toupper(_key);
	}

	allInputKey_.insert(std::make_pair(upperName, GameEngineKey()));
	allInputKey_[upperName].Key_ = _key;
	allInputKey_[upperName].Reset();
}

bool GameEngineInput::IsDown(const std::string& _name)
{
	std::string upperName = GameEngineString::ToUpperReturn(_name);
	if (allInputKey_.end() == allInputKey_.find(upperName))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return allInputKey_[upperName].Down_;
}

bool GameEngineInput::IsUp(const std::string& _name)
{
	std::string upperName = GameEngineString::ToUpperReturn(_name);
	if (allInputKey_.end() == allInputKey_.find(upperName))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return allInputKey_[upperName].Up_;
}

bool GameEngineInput::IsPress(const std::string& _name)
{
	std::string upperName = GameEngineString::ToUpperReturn(_name);
	if (allInputKey_.end() == allInputKey_.find(upperName))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return allInputKey_[upperName].Press_;
}

bool GameEngineInput::IsFree(const std::string& _name)
{
	std::string upperName = GameEngineString::ToUpperReturn(_name);
	if (allInputKey_.end() == allInputKey_.find(upperName))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return allInputKey_[upperName].Free_;
}

bool GameEngineInput::IsKey(const std::string& _name)
{
	std::string upperName = GameEngineString::ToUpperReturn(_name);
	return allInputKey_.end() != allInputKey_.find(upperName);
}


