#include "AccessoryUI.h"

AccessoryUI::AccessoryUI() 
{
}

AccessoryUI::~AccessoryUI() 
{
}

void AccessoryUI::SetAccessory(AccessoryType _Type)
{
	int SelectInt = static_cast<int>(_Type);
	for (int i = 0; i < RendererVector_.size(); i++)
	{
		if (SelectInt == i)
		{
			RendererVector_[i]->On();
		}
		else
		{
			RendererVector_[i]->Off();
		}
	}
}

void AccessoryUI::Start()
{
	SetPosition({ 80, 650 });

	RendererVector_.push_back(CreateRenderer("trinket_001_swallowedpenny.bmp"));
	RendererVector_.push_back(CreateRenderer("trinket_002_petrifiedpoop.bmp"));
	RendererVector_.push_back(CreateRenderer("trinket_003_aaabattery.bmp"));
	RendererVector_.push_back(CreateRenderer("trinket_004_brokenremote.bmp"));
	RendererVector_.push_back(CreateRenderer("trinket_005_purpleheart.bmp"));
	RendererVector_.push_back(CreateRenderer("trinket_006_brokenmagnet.bmp"));
	RendererVector_.push_back(CreateRenderer("trinket_008_cartridge.bmp"));
	RendererVector_.push_back(CreateRenderer("trinket_009_pulseworm.bmp"));

	for (int i = 0; i < RendererVector_.size(); i++)
	{
		RendererVector_[i]->Off();
	}
}

void AccessoryUI::Update()
{

}