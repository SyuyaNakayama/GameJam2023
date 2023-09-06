#pragma once
#include "BaseScene.h"
#include "Stage.h"

class GamePlayScene : public BaseScene
{
	ViewProjection viewProjection;
	Stage stage;

	void Initialize();
	void Update();
	void Draw();

	void display();
	bool isHit(int argMinoX, int argMinoY, int argMinoType, int argMinoAngle);
    void resetMino();

private:
	static const int FIELD_WIDTH = 12;
	static const int FIELD_HEIGHT = 22;

	static const int MINO_WIDTH = 4;
	static const int MINO_HEIGHT = 4;

	enum
	{
		MINO_TYPE_I,
		MINO_TYPE_O,
		MINO_TYPE_S,
		MINO_TYPE_Z,
		MINO_TYPE_J,
		MINO_TYPE_L,
		MINO_TYPE_T,
		MINO_TYPE_MAX
	};

	enum
	{
		MINO_ANGLE_0,
		MINO_ANGLE_90,
		MINO_ANGLE_180,
		MINO_ANGLE_270,
		MINO_ANGLE_MAX
	};

    int minoShapes[MINO_TYPE_MAX][MINO_ANGLE_MAX][MINO_WIDTH][MINO_HEIGHT] =
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
	//　　　　　　　　y   x
	Object3d* blocks[22][12];

    int field[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };

    int displayBuffer[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };

    int fall[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };

    int sam[21];
    int deleteNum;
};