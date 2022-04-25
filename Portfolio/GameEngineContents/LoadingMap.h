#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class LoadingMap : public GameEngineActor
{
public:
	// constrcuter destructer
	LoadingMap();
	~LoadingMap();

	// delete Function
	LoadingMap(const LoadingMap& _Other) = delete;
	LoadingMap(LoadingMap&& _Other) noexcept = delete;
	LoadingMap& operator=(const LoadingMap& _Other) = delete;
	LoadingMap& operator=(LoadingMap&& _Other) noexcept = delete;

protected:

private:
	std::vector<GameEngineRenderer*> FloorMaps_;
	GameEngineRenderer* PlayerRenderer_;

	void Start() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
};

