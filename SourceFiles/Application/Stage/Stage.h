#pragma once
#include <array>
#include "Block.h"

class Stage
{
private:
	static const int FIELD_WIDTH = 12;
	static const int FIELD_HEIGHT = 22;

	static const int MINO_WIDTH = 4;
	static const int MINO_HEIGHT = 4;

	Input* input = Input::GetInstance();

	enum class MinoType { I, O, S, Z, J, L, T, Max };

	enum class MinoAngle { _0, _90, _180, _270, Max };

	int minoShapes[(int)MinoType::Max][(int)MinoAngle::Max][MINO_WIDTH][MINO_HEIGHT] =
	{
		// MINO_TYPE_I
		{
			// MINO_ANGLE_0
			{
				0, 1, 0, 0,
				0, 1, 0, 0,
				0, 1, 0, 0,
				0, 1, 0, 0
			},
		// MINO_ANGLE_90
		{
			0, 0, 0, 0,
			0, 0, 0, 0,
			1, 1, 1, 1,
			0, 0, 0, 0
		},
		// MINO_ANGLE_180
		{
			0, 0, 1, 0,
			0, 0, 1, 0,
			0, 0, 1, 0,
			0, 0, 1, 0
		},
		// MINO_ANGLE_270
		{
			0, 0, 0, 0,
			1, 1, 1, 1,
			0, 0, 0, 0,
			0, 0, 0, 0
		}
	},

		// MINO_TYPE_O
		{
			// MINO_ANGLE_0
			{
				0, 0, 0, 0,
				0, 1, 1, 0,
				0, 1, 1, 0,
				0, 0, 0, 0
			},
		// MINO_ANGLE_90
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		},
		// MINO_ANGLE_180
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		},
		// MINO_ANGLE_270
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		}
	},

		// MINO_TYPE_S
		{
			// MINO_ANGLE_0
			{
				0, 0, 0, 0,
				0, 1, 1, 0,
				1, 1, 0, 0,
				0, 0, 0, 0
			},
		// MINO_ANGLE_90
		{
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0
		},
		// MINO_ANGLE_180
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			1, 1, 0, 0,
			0, 0, 0, 0
		},
		// MINO_ANGLE_270
		{
			0, 0, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 0
		}
	},

		// MINO_TYPE_Z
		{
			// MINO_ANGLE_0
			{
				0, 0, 0, 0,
				1, 1, 0, 0,
				0, 1, 1, 0,
				0, 0, 0, 0
			},
		// MINO_ANGLE_90
		{
			0, 0, 0, 0,
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 1, 0, 0
		},
		// MINO_ANGLE_180
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 1,
			0, 0, 0, 0
		},
		// MINO_ANGLE_270
		{
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		}
	},

		// MINO_TYPE_J
		{
			// MINO_ANGLE_0
			{
				0, 0, 1, 0,
				0, 0, 1, 0,
				0, 1, 1, 0,
				0, 0, 0, 0
			},
		// MINO_ANGLE_90
		{
			0, 0, 0, 0,
			1, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0
		},
		// MINO_ANGLE_180
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 1, 0, 0
		},
		// MINO_ANGLE_270
		{
			0, 0, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 1,
			0, 0, 0, 0
		}
	},

		// MINO_TYPE_L
		{
			// MINO_ANGLE_0
			{
				0, 1, 0, 0,
				0, 1, 0, 0,
				0, 1, 1, 0,
				0, 0, 0, 0
			},
		// MINO_ANGLE_90
		{
			0, 0, 0, 0,
			0, 0, 1, 0,
			1, 1, 1, 0,
			0, 0, 0, 0
		},
		// MINO_ANGLE_180
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 1, 0
		},
		// MINO_ANGLE_270
		{
			0, 0, 0, 0,
			0, 1, 1, 1,
			0, 1, 0, 0,
			0, 0, 0, 0
		}
	},

		// MINO_TYPE_T
		{
			// MINO_ANGLE_0
			{
				0, 0, 0, 0,
				1, 1, 1, 0,
				0, 1, 0, 0,
				0, 0, 0, 0
			},
		// MINO_ANGLE_90
		{
			0, 0, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 1, 0, 0
		},
		// MINO_ANGLE_180
		{
			0, 0, 0, 0,
			0, 0, 1, 0,
			0, 1, 1, 1,
			0, 0, 0, 0
		},
		// MINO_ANGLE_270
		{
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0
		}
	}
	};

	int minoType = 0;
	int minoAngle = 0;
	int minoX = 0;
	int minoY = 0;

	bool isflag = true;
	//bool isLineFilled = true;
	RealTimer Mtimer;
	RealTimer fallTimer = 0.03f;
	int holdTimeA = 0;
	int holdTimeD = 0;
	std::array<std::array<Block, FIELD_WIDTH>, FIELD_HEIGHT> blocks;
	std::array<std::array<int, FIELD_WIDTH>, FIELD_HEIGHT> field;
	std::array<std::array<int, FIELD_WIDTH>, FIELD_HEIGHT> displayBuffer;
	std::array<std::array<int, FIELD_WIDTH>, FIELD_HEIGHT> fall;

	int sam[21];
	int deleteNum;

	void Display();
	bool IsHit(int argMinoX, int argMinoY, int argMinoType, int argMinoAngle);
	void ResetMino();

public:
	void Initialize();
	void Update();
};