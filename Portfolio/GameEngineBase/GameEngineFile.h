#pragma once
#include "GameEnginePath.h"

enum class OpenMode
{
	Read,
	Write,
};

// Ό³Έν :
class GameEngineFile : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineFile();
	GameEngineFile(const char* _Path);
	GameEngineFile(std::filesystem::path _path);
	GameEngineFile(const GameEngineFile& _Other);
	~GameEngineFile();

	void Open(OpenMode _Mode);
	inline void ReadOpen()
	{
		Open(OpenMode::Read);
	}
	inline void WriteOpen()
	{
		Open(OpenMode::Write);
	}

	void Close();
	inline void Create()
	{
		Open(OpenMode::Write);
		Close();
	}
protected:

private:
	FILE* FilePtr;
};

