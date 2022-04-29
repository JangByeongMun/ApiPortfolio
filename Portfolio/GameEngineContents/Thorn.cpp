#include "Thorn.h"

Thorn::Thorn()
	: Renderer_(nullptr)
	, ShadowRenderer_(nullptr)
	, Collision_(nullptr)
	, Type_(ThornType::Default)
{
}

Thorn::~Thorn() 
{
}

void Thorn::SetType(ThornType _Type)
{
	Type_ = _Type;
	Renderer_ = CreateRenderer("grid_spikes.bmp");
	ShadowRenderer_ = CreateRenderer("grid_spikes_Shadow.bmp");
	Collision_ = CreateCollision("Thron", {50, 50});
}

void Thorn::Update()
{

}