#pragma once
#include <array>
#include "Block.h"
#include "Input.h"
#include "Timer.h"

enum class MinoType { I, O, S, Z, J, L, T, Max };

enum class MinoAngle { _0, _90, _180, _270, Max };

struct Mino
{
	int type = 0;
	int angle = 0;
	int posX = 0;
	int posY = 0;
	int shadowY = 0;
	bool isEarth = false;

	void Reset();
};

class Stage
{
private:
	static const int FIELD_WIDTH = 12;
	static const int FIELD_HEIGHT = 22;
	static const int MINO_WIDTH = 4;
	static const int MINO_HEIGHT = 4;
	static const int TO_MOVE_TIME = 10;

	Input* input = Input::GetInstance();

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

	Mino mino;

	RealTimer Mtimer = 1.0f;
	RealTimer fallTimer = 0.03f;
	int holdTimeA = 0;
	int holdTimeD = 0;
	std::array<std::array<Block, FIELD_WIDTH>, FIELD_HEIGHT> blocks;
	std::array<std::array<int, FIELD_WIDTH>, FIELD_HEIGHT> field;
	std::array<std::array<int, FIELD_WIDTH>, FIELD_HEIGHT> displayBuffer;

	std::array<int, 21> sum;
	int deleteNum;

	bool isEnd = false; //èIóπÉtÉâÉO
	int score = 0;

	void Display();
	bool IsHit(int argMinoX, int argMinoY, int argMinoAngle);
	void ShowImGui();
	void MoveMino();
	void MinoSet();

public:
	void Initialize();
	void Update();
	bool IsEnd() { return isEnd; }
};