#include "GameEngineInput.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

////////////////////////////////////////////////// GameEngineKey
void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
	if (true == KeyCheck())
	{
		if (true == Free_)
		{
			Down_ = true;
			Press_ = true;
			Up_ = false;
			Free_ = false;
			Time_ = 0.0f;
			Time_ += _DeltaTime;
		}
		else if (true == Press_)
		{
			Down_ = false;
			Press_ = true;
			Up_ = false;
			Free_ = false;
			Time_ += _DeltaTime;
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
			Time_ = 0.0f;
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
	: CurWheelValue()
{
}

GameEngineInput::~GameEngineInput() 
{
}

void GameEngineInput::Update(float _DeltaTime)
{
	CurWheelValue = 0;
	CurWheelValue = WheelValue;
	WheelValue = 0;

	std::map<std::string, GameEngineKey>::iterator KeyUpdateStart = AllInputKey_.begin();
	std::map<std::string, GameEngineKey>::iterator KeyUpdateEnd = AllInputKey_.end();
	
	for (; KeyUpdateStart != KeyUpdateEnd; ++KeyUpdateStart)
	{
		GameEngineKey& CurrentKey = KeyUpdateStart->second;
		CurrentKey.Update(_DeltaTime);
	}
}

void GameEngineInput::CreateKey(const std::string& _Name, int _Key)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	if (AllInputKey_.end() != AllInputKey_.find(UpperName))
	{
		MsgBoxAssert("이미 존재하는 이름의 키를 또 만들려고 했습니다");
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

float GameEngineInput::GetTime(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);
	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}

	return AllInputKey_[UpperKey].Time_;
}

bool GameEngineInput::IsDown(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	if (AllInputKey_.end() == AllInputKey_.find(UpperName))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return AllInputKey_[UpperName].Down_;
}

bool GameEngineInput::IsUp(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	if (AllInputKey_.end() == AllInputKey_.find(UpperName))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return AllInputKey_[UpperName].Up_;
}

bool GameEngineInput::IsPress(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	if (AllInputKey_.end() == AllInputKey_.find(UpperName))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return AllInputKey_[UpperName].Press_;
}

bool GameEngineInput::IsFree(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	if (AllInputKey_.end() == AllInputKey_.find(UpperName))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return AllInputKey_[UpperName].Free_;
}

bool GameEngineInput::IsKey(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() != AllInputKey_.find(UpperName))
	{
		return true;
	}

	return false;
}


