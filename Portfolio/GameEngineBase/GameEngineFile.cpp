#include "GameEngineFile.h"

GameEngineFile::GameEngineFile() 
{
}

GameEngineFile::GameEngineFile(const std::string& _path)
{
	path_ = _path;
}

GameEngineFile::GameEngineFile(std::filesystem::path _path)
{
	path_ = _path;
}

GameEngineFile::GameEngineFile(const GameEngineFile& _Other)
{
	path_ = _Other.path_;
}

GameEngineFile::~GameEngineFile() 
{
}

