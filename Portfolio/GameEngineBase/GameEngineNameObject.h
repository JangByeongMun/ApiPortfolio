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

	inline void SetName(const std::string& _Name)
	{
		Name_ = _Name;
	}
	inline std::string GetName()
	{
		return Name_;
	}
	inline std::string& GetNameRef()
	{
		return Name_;
	}
	inline const char* GetNamePtr()
	{
		return Name_.c_str();
	}

protected:

private:
	std::string Name_;
};

