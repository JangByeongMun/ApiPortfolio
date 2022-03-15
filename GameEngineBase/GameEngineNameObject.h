#pragma once
#include <string>

// Ό³Έν :
class GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineNameObject();
	virtual ~GameEngineNameObject();

	// delete Function
	GameEngineNameObject(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject(GameEngineNameObject&& _Other) noexcept = delete;
	GameEngineNameObject& operator=(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject& operator=(GameEngineNameObject&& _Other) noexcept = delete;

	inline void SetName(const std::string& _name)
	{
		name_ = _name;
	}
	const inline std::string GetName() 
	{
		return name_;
	}
	const inline std::string& GetNameRef()
	{
		return name_;
	}
	const inline char* GetNamePtr()
	{
		return name_.c_str();
	}

private:
	std::string name_;
};

