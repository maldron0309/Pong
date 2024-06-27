#include <stdio.h>
#include <raylib.h>

const int screenWidth = 1200;
const int screenHeight = 800;

class Player
{
};

class Computer
{
};

class Game
{
public:
    Player player;
    Computer computer;


};

int
main()
{
    SetTargetFPS(60);

    InitWindow(screenWidth, screenHeight, "Pong");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
        DrawCircle(screenWidth / 2, screenHeight / 2, 10, WHITE);
        DrawRectangle(10, screenHeight / 2 - 60, 25, 125, WHITE);
        DrawRectangle(screenWidth - 35, screenHeight / 2 - 60, 25, 125, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}