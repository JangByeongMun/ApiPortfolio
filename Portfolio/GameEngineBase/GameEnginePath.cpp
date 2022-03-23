#include "GameEnginePath.h"

GameEnginePath::GameEnginePath() 
{
}

GameEnginePath::GameEnginePath(const std::filesystem::path _path)
{
	path_ = _path;
}

GameEnginePath::~GameEnginePath() 
{
}

void GameEnginePath::SetCurrentPath()
{
	path_ = std::filesystem::current_path();
}

bool GameEnginePath::IsExists()
{
	return std::filesystem::exists(path_);
}

std::string GameEnginePath::GetExtension()
{
	return path_.extension().string();
}

std::string GameEnginePath::GetFileName()
{
	return path_.filename().string();
}

std::string GameEnginePath::GetFullPath()
{
	return path_.string();
}
