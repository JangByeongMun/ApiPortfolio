#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>

enum class NodeState
{
	Unknown,
	Near,
	Past,
	Current,
};

class MapNode
{
public:
	float4 Pos_;
	NodeState State_;
	GameEngineRenderer* Renderer_;
	GameEngineRenderer* IconRenderer_;
};

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
	
	void MakeNode();
	void ChangeMap(float4 _Dir);
	void SeeAllMap();

protected:

private:
	std::vector<MapNode*> NodeVecter_;
	void Start() override;

	bool IsInsideNode(float4 _Pivot);
};

