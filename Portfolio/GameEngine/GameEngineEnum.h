#pragma once

enum class RenderPivot
{
	CENTER,
	BOT,
};

enum class RenderScaleMode
{
	Image,
	User,
};

// 선택한 캐릭터 타입
enum class CharacterType
{
	ISAAC,
	MAGDALENE,
	CAIN,
	JUDAS,
	EVE,
	BLUEBABY,
	SAMSON,
	AZAZEL
};

// 각 블럭의 데이터값
enum class BlockData
{
	NORMAL = 0,
	FIRE,
	FIREBLUE,
	FIRERED,
	HOLE,
	POOP,
	POOPRED,
	STONE,
	STONEBLACK,
	THORN,

	END,
};