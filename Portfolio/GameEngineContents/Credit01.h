#pragma once
#include <GameEngine/GameEngineActor.h>

class Credit01 : public GameEngineActor
{
public:
	// constrcuter destructer
	Credit01();
	~Credit01();

	// delete Function
	Credit01(const Credit01& _Other) = delete;
	Credit01(Credit01&& _Other) noexcept = delete;
	Credit01& operator=(const Credit01& _Other) = delete;
	Credit01& operator=(Credit01&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

