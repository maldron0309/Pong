#include <stdio.h>
#include <raylib.h>

const int screenWidth = 1200;
const int screenHeight = 800;



class Ball
{
public:
    float x,y;
    float speedX, speedY;;
    int radius;

    void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }

    void Update()
    {
        x += speedX;
        y += speedY;

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speedY *= -1;
        }

        if (x + radius >= GetScreenWidth() || x - radius <= 0)
        {
            speedX *= -1;
        }
        
        
    }
};

class Paddle
{
public:
    float x,y;
    int width, height;
    int speed;
    
    void Draw()
    {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Update()
    {
        if (IsKeyDown(KEY_UP))
        {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y += speed;
        }

        if (y <= 0)
        {
            y = 0;
        }
        
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
        
        
    }
};


Ball ball;
Paddle player;

int main()
{
    SetTargetFPS(60);

    ball.radius = 15;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speedX = 10;
    ball.speedY = 10;

    player.width = 25;
    player.height = 125;
    player.x = screenWidth - player.width - 10;
    player.y = screenHeight / 2 - player.height / 2;
    player.speed = 10;

    

    InitWindow(screenWidth, screenHeight, "Pong");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
        
        ball.Draw();
        ball.Update();

        player.Draw();
        player.Update();

        ClearBackground(BLACK);
        DrawCircle(screenWidth / 2, screenHeight / 2, 10, WHITE);
        DrawRectangle(10, screenHeight / 2 - 60, 25, 125, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}