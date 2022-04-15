#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class MiniMap : public GameEngineActor
{
public:
	// constrcuter destructer
	MiniMap();
	~MiniMap();

	// delete Function
	MiniMap(const MiniMap& _Other) = delete;
	MiniMap(MiniMap&& _Other) noexcept = delete;
	MiniMap& operator=(const MiniMap& _Other) = delete;
	MiniMap& operator=(MiniMap&& _Other) noexcept = delete;

protected:

private:
	
	void Start() override;
	void Update() override;
};

