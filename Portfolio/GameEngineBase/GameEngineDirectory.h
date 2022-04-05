#pragma once
#include "GameEnginePath.h"

class GameEngineFile;
class GameEngineDirectory : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineDirectory();
	GameEngineDirectory(const std::string& _Path);
	~GameEngineDirectory();

	// delete Function
	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;

	void Move(const std::string& _Name);
	void MoveParent();
	void MoveParent(const std::string& _Name);
	bool IsRoot();

	// 확장자명을 받아서 현재위치의 해당 확장자를 가진 파일들 전부 가져오는함수
	std::vector<GameEngineFile> GetAllFile(const std::string& _Ext = "");

protected:

private:

};

