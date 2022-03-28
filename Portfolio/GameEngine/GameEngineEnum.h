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

// ������ ĳ���� Ÿ��
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

// �� ���� �����Ͱ�
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