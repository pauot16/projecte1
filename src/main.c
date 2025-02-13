#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"

/////////////////////////////////////// CUSTOM FACTORS (PHYSICS) //////////////////////////////////////

#define G 400
#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 200.0f

/////////////////////////////////////// STRUCTS //////////////////////////////////////////////////////

typedef struct Player {
	Vector2 position;
	float speed;
	bool canJump;
} Player;

typedef struct EnvItem {
	Rectangle character;
	int blocking;
	Color color;
} EnvItem;

/////////////////////////////////////// MODULE FUNCTIONS /////////////////////////////////////////////

void UpdatePlayer(Player* player, EnvItem* envItems, int envItemsLength, float delta);
void UpdateCameraCenter(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraCenterInsideMap(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraCenterSmoothFollow(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraEvenOutOnLanding(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraPlayerBoundsPush(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);

////////////////////////////////////// MAIN ////////////////////////////////////////////////////////

int main (void)
{
	InitWindow(2040, 1080, "FOXY");

	Player player = { 0 };
	player.position = (Vector2){ 400, 0 };
	player.speed = 0;
	player.canJump = false;  
	EnvItem envItems[] = {
		{{ 0, 0, 1000, 400 }, 0, LIGHTGRAY },
		{{ 0, 400, 1000, 200 }, 1, GRAY },
		{{ 300, 200, 400, 10 }, 1, GRAY },
		{{ 250, 300, 100, 10 }, 1, GRAY },
		{{ 650, 300, 100, 10 }, 1, GRAY }
	};

	



	CloseWindow();
	return 0;
}

