#pragma once
#include "GameEngine/GameEngineLevel.h"

// 설명 : 아이작에서 층마다 넘어갈때의 화면
class LoadingLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	LoadingLevel();
	~LoadingLevel();

	// delete Function
	LoadingLevel(const LoadingLevel& _Other) = delete;
	LoadingLevel(LoadingLevel&& _Other) noexcept = delete;
	LoadingLevel& operator=(const LoadingLevel& _Other) = delete;
	LoadingLevel& operator=(LoadingLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

	void SceneChangeStart() override;
	void SceneChangeEnd() override;

private:

};

