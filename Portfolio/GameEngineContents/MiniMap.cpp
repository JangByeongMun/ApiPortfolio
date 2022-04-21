#include "MiniMap.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include "RandomRoomManager.h"
#include "RoomActor.h"
#include "Player.h"

MiniMap::MiniMap() 
{
}
MiniMap::~MiniMap() 
{
	for (int i = 0; i < NodeVecter_.size(); i++)
	{
		if (nullptr != NodeVecter_[i])
		{
			delete NodeVecter_[i];
			NodeVecter_[i] = nullptr;
		}
	}
}

void MiniMap::Start()
{
	SetPosition({ 1150, 100 });

	CreateRenderer("minimap_Frame.bmp")->CameraEffectOff();
	GameEngineRenderer* Renderer = CreateRenderer("minimap_BG.bmp");
	Renderer->CameraEffectOff();
	Renderer->SetAlpha(100);
}

bool MiniMap::IsInsideNode(float4 _Pivot)
{
	if (
		2 * 25.0f >= _Pivot.ix() && _Pivot.ix() >= -2 * 25.0f &&
		2 * 25.0f >= _Pivot.iy() && _Pivot.iy() >= -2 * 25.0f
		)
	{
		return true;
	}
	
	return false;
}

void MiniMap::MakeNode()
{
	std::vector<RoomActor*> TmpRooms = RandomRoomManager::GetInst()->GetCurrentRooms();
	for (int i = 0; i < TmpRooms.size(); i++)
	{
		MapNode* TmpNode = new MapNode();
		TmpNode->Pos_ = TmpRooms[i]->GetPos();
		TmpNode->Renderer_ = CreateRenderer("minimap1.bmp", RenderPivot::CENTER, TmpNode->Pos_ * 25.0f);
		TmpNode->Renderer_->SetIndex(36);
		TmpNode->Renderer_->CameraEffectOff();
		TmpNode->IconRenderer_ = nullptr;
		TmpNode->State_ = NodeState::Unknown;

		if (RoomType::Boss == TmpRooms[i]->GetData().GetRoomType())
		{
			TmpNode->IconRenderer_ = CreateRenderer("minimap1.bmp", RenderPivot::CENTER, TmpNode->Pos_ * 25.0f);
			TmpNode->IconRenderer_->SetIndex(11);
			TmpNode->IconRenderer_->Off();
			TmpNode->IconRenderer_->CameraEffectOff();
		}
		if (RoomType::Treasure == TmpRooms[i]->GetData().GetRoomType())
		{
			TmpNode->IconRenderer_ = CreateRenderer("minimap1.bmp", RenderPivot::CENTER, TmpNode->Pos_ * 25.0f);
			TmpNode->IconRenderer_->SetIndex(8);
			TmpNode->IconRenderer_->Off();
			TmpNode->IconRenderer_->CameraEffectOff();
		}

		NodeVecter_.push_back(TmpNode);
	}
}

void MiniMap::ChangeMap(float4 _Dir)
{
	// 근처 노드들 위치 확인해서 상태변경
	float4 CurrnetPos = Player::MainPlayer->GetCurrentRoomPos();
	for (int i = 0; i < NodeVecter_.size(); i++)
	{
		if (NodeVecter_[i]->Pos_.CompareInt2D(Player::MainPlayer->GetCurrentRoomPos())) // 이동한곳 일때
		{
			NodeVecter_[i]->State_ = NodeState::Current;
		}
		else if (
			NodeVecter_[i]->Pos_.CompareInt2D(CurrnetPos + float4(1, 0)) ||
			NodeVecter_[i]->Pos_.CompareInt2D(CurrnetPos + float4(-1, 0)) ||
			NodeVecter_[i]->Pos_.CompareInt2D(CurrnetPos + float4(0, 1)) ||
			NodeVecter_[i]->Pos_.CompareInt2D(CurrnetPos + float4(0, -1))
			) // 이동한곳 근처
		{
			switch (NodeVecter_[i]->State_)
			{
			case NodeState::Unknown:
			case NodeState::Near:
				NodeVecter_[i]->State_ = NodeState::Near;
				break;
			case NodeState::Past:
			case NodeState::Current:
				NodeVecter_[i]->State_ = NodeState::Past;
				break;
			default:
				break;
			}
		}
	}

	// 노드들 변경된 상태로 그림
	for (int i = 0; i < NodeVecter_.size(); i++)
	{
		switch (NodeVecter_[i]->State_)
		{
		case NodeState::Unknown:
			NodeVecter_[i]->Renderer_->SetIndex(36);
			if (nullptr != NodeVecter_[i]->IconRenderer_)
			{
				NodeVecter_[i]->IconRenderer_->Off();
			}
			break;
		case NodeState::Near:
			NodeVecter_[i]->Renderer_->SetIndex(2);
			if (nullptr != NodeVecter_[i]->IconRenderer_)
			{
				NodeVecter_[i]->IconRenderer_->On();
			}
			break;
		case NodeState::Past:
			NodeVecter_[i]->Renderer_->SetIndex(1);
			break;
		case NodeState::Current:
			NodeVecter_[i]->Renderer_->SetIndex(14);
			break;
		default:
			break;
		}

		NodeVecter_[i]->Renderer_->SetPivot(NodeVecter_[i]->Renderer_->GetPivot() - _Dir * 25.0f);
		if (nullptr != NodeVecter_[i]->IconRenderer_)
		{
			NodeVecter_[i]->IconRenderer_->SetPivot(NodeVecter_[i]->IconRenderer_->GetPivot() - _Dir * 25.0f);
		}

		if (true == IsInsideNode(NodeVecter_[i]->Renderer_->GetPivot()) && NodeState::Unknown != NodeVecter_[i]->State_)
		{
			NodeVecter_[i]->Renderer_->On();
			if (nullptr != NodeVecter_[i]->IconRenderer_)
			{
				NodeVecter_[i]->IconRenderer_->On();
			}
		}
		else
		{
			NodeVecter_[i]->Renderer_->Off();
			if (nullptr != NodeVecter_[i]->IconRenderer_)
			{
				NodeVecter_[i]->IconRenderer_->Off();
			}
		}
	}
}

void MiniMap::SeeAllMap()
{
	for (int i = 0; i < NodeVecter_.size(); i++)
	{
		NodeVecter_[i]->State_ = NodeState::Past;
		if (nullptr != NodeVecter_[i]->IconRenderer_)
		{
			NodeVecter_[i]->IconRenderer_->On();
		}
	}

	ChangeMap({0, 0});
}
