#include "MiniMap.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include "RandomRoomManager.h"
#include "RoomActor.h"
#include "Player.h"

MiniMap::MiniMap() 
	: IsBigsize_(false)
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

	for (int i = 0; i < BigNodeVecter_.size(); i++)
	{
		if (nullptr != BigNodeVecter_[i])
		{
			delete BigNodeVecter_[i];
			BigNodeVecter_[i] = nullptr;
		}
	}
}

void MiniMap::Start()
{
	SetPosition({ 1150, 100 });

	{
		GameEngineRenderer* Renderer = CreateRenderer("minimap_BG.bmp");
		Renderer->SetAlpha(100 + (10 * (Option_SFX - 5)));
		Renderer->CameraEffectOff();
		FrameRendererVecter_.push_back(Renderer);
	}
	{
		GameEngineRenderer* Renderer = CreateRenderer("minimap_Frame.bmp");
		Renderer->CameraEffectOff();
		FrameRendererVecter_.push_back(Renderer);
	}
	
	if (false == GameEngineInput::GetInst()->IsKey("MinimapTab"))
	{
		GameEngineInput::GetInst()->CreateKey("MinimapTab", VK_TAB);
	}
}

void MiniMap::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("MinimapTab"))
	{
		IsBigsize_ = true;
		for (int i = 0; i < NodeVecter_.size(); i++)
		{
			NodeVecter_[i]->BGRenderer_->Off();
			NodeVecter_[i]->Renderer_->Off();
			if (nullptr != NodeVecter_[i]->IconRenderer_)
			{
				NodeVecter_[i]->IconRenderer_->Off();
			}
		}
		for (int i = 0; i < BigNodeVecter_.size(); i++)
		{
			BigNodeVecter_[i]->BGRenderer_->On();
			BigNodeVecter_[i]->Renderer_->On();
			if (nullptr != BigNodeVecter_[i]->IconRenderer_)
			{
				BigNodeVecter_[i]->IconRenderer_->On();
			}
		}

		for (int i = 0; i < FrameRendererVecter_.size(); i++)
		{
			FrameRendererVecter_[i]->Off();
		}

		ChangeMap({0, 0});
	}

	if (true == GameEngineInput::GetInst()->IsUp("MinimapTab"))
	{
		IsBigsize_ = false;
		for (int i = 0; i < NodeVecter_.size(); i++)
		{
			NodeVecter_[i]->BGRenderer_->On();
			NodeVecter_[i]->Renderer_->On();
			if (nullptr != NodeVecter_[i]->IconRenderer_)
			{
				NodeVecter_[i]->IconRenderer_->On();
			}
		}
		for (int i = 0; i < BigNodeVecter_.size(); i++)
		{
			BigNodeVecter_[i]->BGRenderer_->Off();
			BigNodeVecter_[i]->Renderer_->Off();
			if (nullptr != BigNodeVecter_[i]->IconRenderer_)
			{
				BigNodeVecter_[i]->IconRenderer_->Off();
			}
		}

		for (int i = 0; i < FrameRendererVecter_.size(); i++)
		{
			FrameRendererVecter_[i]->On();
		}
		ChangeMap({ 0, 0 });
	}
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
	// 일반 미니맵
	for (int i = 0; i < TmpRooms.size(); i++)
		{
			MapNode* TmpNode = new MapNode();
			TmpNode->Pos_ = TmpRooms[i]->GetPos();

			float4 CurrentPos = float4(TmpNode->Pos_.x * 25.0f, TmpNode->Pos_.y * 20.0f);

			TmpNode->BGRenderer_ = CreateRenderer("minimap1.bmp", RenderPivot::CENTER, CurrentPos, static_cast<int>(ORDER::BACKUI));
			TmpNode->BGRenderer_->CameraEffectOff();
			TmpNode->BGRenderer_->SetIndex(36);

			TmpNode->Renderer_ = CreateRenderer("minimap1.bmp", RenderPivot::CENTER, CurrentPos, static_cast<int>(ORDER::UI));
			TmpNode->Renderer_->SetIndex(36);
			TmpNode->Renderer_->CameraEffectOff();

			TmpNode->IconRenderer_ = nullptr;

			TmpNode->State_ = NodeState::Unknown;

			if (RoomType::Boss == TmpRooms[i]->GetData().GetRoomType())
			{
				TmpNode->IconRenderer_ = CreateRenderer("minimap1.bmp", RenderPivot::CENTER, CurrentPos, static_cast<int>(ORDER::UI));
				TmpNode->IconRenderer_->SetIndex(11);
				TmpNode->IconRenderer_->Off();
				TmpNode->IconRenderer_->CameraEffectOff();
			}
			if (RoomType::Treasure == TmpRooms[i]->GetData().GetRoomType())
			{
				TmpNode->IconRenderer_ = CreateRenderer("minimap1.bmp", RenderPivot::CENTER, CurrentPos, static_cast<int>(ORDER::UI));
				TmpNode->IconRenderer_->SetIndex(8);
				TmpNode->IconRenderer_->Off();
				TmpNode->IconRenderer_->CameraEffectOff();
			}
			if (RoomType::Shop == TmpRooms[i]->GetData().GetRoomType())
			{
				TmpNode->IconRenderer_ = CreateRenderer("minimap1.bmp", RenderPivot::CENTER, CurrentPos, static_cast<int>(ORDER::UI));
				TmpNode->IconRenderer_->SetIndex(3);
				TmpNode->IconRenderer_->Off();
				TmpNode->IconRenderer_->CameraEffectOff();
			}

			NodeVecter_.push_back(TmpNode);
		}

	// 탭 눌렀을때의 확대 미니맵
	for (int i = 0; i < TmpRooms.size(); i++)
	{
		MapNode* TmpNode = new MapNode();
		TmpNode->Pos_ = TmpRooms[i]->GetPos();

		float4 CurrentPos = float4(TmpNode->Pos_.x * 50.0f, TmpNode->Pos_.y * 45.0f) + float4(-100,100);

		TmpNode->BGRenderer_ = CreateRenderer("minimap2.bmp", RenderPivot::CENTER, CurrentPos, static_cast<int>(ORDER::BACKUI));
		TmpNode->BGRenderer_->CameraEffectOff();
		TmpNode->BGRenderer_->SetIndex(12);

		TmpNode->Renderer_ = CreateRenderer("minimap2.bmp", RenderPivot::CENTER, CurrentPos, static_cast<int>(ORDER::UI));
		TmpNode->Renderer_->SetIndex(12);
		TmpNode->Renderer_->CameraEffectOff();

		TmpNode->IconRenderer_ = nullptr;

		TmpNode->State_ = NodeState::Unknown;

		if (RoomType::Boss == TmpRooms[i]->GetData().GetRoomType())
		{
			TmpNode->IconRenderer_ = CreateRenderer("minimap2.bmp", RenderPivot::CENTER, CurrentPos, static_cast<int>(ORDER::UI));
			TmpNode->IconRenderer_->SetIndex(10);
			TmpNode->IconRenderer_->CameraEffectOff();
			TmpNode->IconRenderer_->Off();
		}
		if (RoomType::Treasure == TmpRooms[i]->GetData().GetRoomType())
		{
			TmpNode->IconRenderer_ = CreateRenderer("minimap2.bmp", RenderPivot::CENTER, CurrentPos, static_cast<int>(ORDER::UI));
			TmpNode->IconRenderer_->SetIndex(9);
			TmpNode->IconRenderer_->CameraEffectOff();
			TmpNode->IconRenderer_->Off();
		}
		if (RoomType::Shop == TmpRooms[i]->GetData().GetRoomType())
		{
			TmpNode->IconRenderer_ = CreateRenderer("minimap2.bmp", RenderPivot::CENTER, CurrentPos, static_cast<int>(ORDER::UI));
			TmpNode->IconRenderer_->SetIndex(6);
			TmpNode->IconRenderer_->CameraEffectOff();
			TmpNode->IconRenderer_->Off();
		}

		BigNodeVecter_.push_back(TmpNode);
	}
	for (int i = 0; i < BigNodeVecter_.size(); i++)
	{
		BigNodeVecter_[i]->BGRenderer_->Off();
		BigNodeVecter_[i]->Renderer_->Off();
		if (nullptr != BigNodeVecter_[i]->IconRenderer_)
		{
			BigNodeVecter_[i]->IconRenderer_->Off();
		}
	}

	if (true == Player::MainPlayer->Have246())
	{
		SeeSpecialRooms();
	}
}

void MiniMap::ChangeMap(float4 _Dir)
{
	float4 CurrnetPos = Player::MainPlayer->GetCurrentRoomPos();

	// 근처 노드들 위치 확인해서 상태변경
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
	for (int i = 0; i < BigNodeVecter_.size(); i++)
	{
		if (BigNodeVecter_[i]->Pos_.CompareInt2D(Player::MainPlayer->GetCurrentRoomPos())) // 이동한곳 일때
		{
			BigNodeVecter_[i]->State_ = NodeState::Current;
		}
		else if (
			BigNodeVecter_[i]->Pos_.CompareInt2D(CurrnetPos + float4(1, 0)) ||
			BigNodeVecter_[i]->Pos_.CompareInt2D(CurrnetPos + float4(-1, 0)) ||
			BigNodeVecter_[i]->Pos_.CompareInt2D(CurrnetPos + float4(0, 1)) ||
			BigNodeVecter_[i]->Pos_.CompareInt2D(CurrnetPos + float4(0, -1))
			) // 이동한곳 근처
		{
			switch (BigNodeVecter_[i]->State_)
			{
			case NodeState::Unknown:
			case NodeState::Near:
				BigNodeVecter_[i]->State_ = NodeState::Near;
				break;
			case NodeState::Past:
			case NodeState::Current:
				BigNodeVecter_[i]->State_ = NodeState::Past;
				break;
			default:
				break;
			}
		}
	}

	// 일반 미니맵
	if (false == IsBigsize_)
	{
		// 노드들 변경된 상태로 그림
		for (int i = 0; i < NodeVecter_.size(); i++)
		{
			switch (NodeVecter_[i]->State_)
			{
			case NodeState::Unknown:
				NodeVecter_[i]->BGRenderer_->SetIndex(36);
				NodeVecter_[i]->Renderer_->SetIndex(36);
				if (nullptr != NodeVecter_[i]->IconRenderer_)
				{
					NodeVecter_[i]->IconRenderer_->Off();
				}
				break;
			case NodeState::Near:
				NodeVecter_[i]->BGRenderer_->SetIndex(0);
				NodeVecter_[i]->Renderer_->SetIndex(2);
				if (nullptr != NodeVecter_[i]->IconRenderer_)
				{
					NodeVecter_[i]->IconRenderer_->On();
				}
				break;
			case NodeState::Past:
				NodeVecter_[i]->BGRenderer_->SetIndex(0);
				NodeVecter_[i]->Renderer_->SetIndex(1);
				break;
			case NodeState::Current:
				NodeVecter_[i]->BGRenderer_->SetIndex(0);
				NodeVecter_[i]->Renderer_->SetIndex(14);
				break;
			default:
				break;
			}

			NodeVecter_[i]->BGRenderer_->SetPivot(NodeVecter_[i]->BGRenderer_->GetPivot() - _Dir * 25.0f);
			NodeVecter_[i]->Renderer_->SetPivot(NodeVecter_[i]->Renderer_->GetPivot() - _Dir * 25.0f);
			if (nullptr != NodeVecter_[i]->IconRenderer_)
			{
				NodeVecter_[i]->IconRenderer_->SetPivot(NodeVecter_[i]->IconRenderer_->GetPivot() - _Dir * 25.0f);
			}

			if (true == IsInsideNode(NodeVecter_[i]->Renderer_->GetPivot()) && NodeState::Unknown != NodeVecter_[i]->State_)
			{
				NodeVecter_[i]->BGRenderer_->On();
				NodeVecter_[i]->Renderer_->On();
				if (nullptr != NodeVecter_[i]->IconRenderer_)
				{
					NodeVecter_[i]->IconRenderer_->On();
				}
			}
			else
			{
				NodeVecter_[i]->BGRenderer_->Off();
				NodeVecter_[i]->Renderer_->Off();
				if (nullptr != NodeVecter_[i]->IconRenderer_)
				{
					NodeVecter_[i]->IconRenderer_->Off();
				}
			}
		}
	}
	else // 탭 누른 큰 미니맵
	{
		for (int i = 0; i < BigNodeVecter_.size(); i++)
		{
			switch (BigNodeVecter_[i]->State_)
			{
			case NodeState::Unknown:
				BigNodeVecter_[i]->BGRenderer_->SetIndex(12);
				BigNodeVecter_[i]->Renderer_->SetIndex(12);
				if (nullptr != BigNodeVecter_[i]->IconRenderer_)
				{
					BigNodeVecter_[i]->IconRenderer_->Off();
				}
				break;
			case NodeState::Near:
				BigNodeVecter_[i]->BGRenderer_->SetIndex(0);
				BigNodeVecter_[i]->Renderer_->SetIndex(7);
				if (nullptr != BigNodeVecter_[i]->IconRenderer_)
				{
					BigNodeVecter_[i]->IconRenderer_->On();
				}
				break;
			case NodeState::Past:
				BigNodeVecter_[i]->BGRenderer_->SetIndex(0);
				BigNodeVecter_[i]->Renderer_->SetIndex(1);
				break;
			case NodeState::Current:
				BigNodeVecter_[i]->BGRenderer_->SetIndex(0);
				BigNodeVecter_[i]->Renderer_->SetIndex(11);
				break;
			default:
				break;
			}

			//if (true == IsInsideNode(BigNodeVecter_[i]->Renderer_->GetPivot()) && NodeState::Unknown != BigNodeVecter_[i]->State_)
			//{
			//	BigNodeVecter_[i]->BGRenderer_->On();
			//	BigNodeVecter_[i]->Renderer_->On();
			//	if (nullptr != BigNodeVecter_[i]->IconRenderer_)
			//	{
			//		BigNodeVecter_[i]->IconRenderer_->On();
			//	}
			//}
			//else
			//{
			//	BigNodeVecter_[i]->BGRenderer_->Off();
			//	BigNodeVecter_[i]->Renderer_->Off();
			//	if (nullptr != BigNodeVecter_[i]->IconRenderer_)
			//	{
			//		BigNodeVecter_[i]->IconRenderer_->Off();
			//	}
			//}
		}
	}
}

void MiniMap::SeeAllMap()
{
	for (int i = 0; i < NodeVecter_.size(); i++)
	{
		NodeVecter_[i]->State_ = NodeState::Past;
	}

	for (int i = 0; i < BigNodeVecter_.size(); i++)
	{
		BigNodeVecter_[i]->State_ = NodeState::Past;
	}

	ChangeMap({0, 0});
}

void MiniMap::SeeSpecialRooms()
{
	for (int i = 0; i < NodeVecter_.size(); i++)
	{
		if (nullptr != NodeVecter_[i]->IconRenderer_)
		{
			NodeVecter_[i]->State_ = NodeState::Past;
		}
	}

	for (int i = 0; i < BigNodeVecter_.size(); i++)
	{
		if (nullptr != BigNodeVecter_[i]->IconRenderer_)
		{
			BigNodeVecter_[i]->State_ = NodeState::Past;
		}
	}

	ChangeMap({ 0, 0 });
}
