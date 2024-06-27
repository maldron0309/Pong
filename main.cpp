#include <stdio.h>
#include <raylib.h>

const int screenWidth = 1200;
const int screenHeight = 800;

int playerScore = 0;
int computerScore = 0;

class Ball
{
public:
    float x, y;
    float speedX, speedY;
    ;
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

        if (x + radius >= GetScreenWidth())
        {
            computerScore++;
            ResetBall();
        }

        if (x - radius <= 0)
        {
            playerScore++;
            ResetBall();
        }
    }

    void ResetBall()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        
        int speedChoices[2] = {-1,1};
        speedX *= speedChoices[GetRandomValue(0,1)];
        speedY *= speedChoices[GetRandomValue(0,1)];
    }
};

class Player
{

protected:
    void LimitMovement()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
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

class Computer : public Player
{
public:
    void Update(int ballY)
    {
        if (y + height / 2 <= ballY)
        {
            y += speed;
        }
        if (y + height / 2 > ballY)
        {
            y -= speed;
        }

        LimitMovement();
    }
};

Ball ball;
Player player;
Computer computer;

int main()
{
    SetTargetFPS(60);

    ball.radius = 15;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speedX = 7;
    ball.speedY = 7;

    player.width = 20;
    player.height = 120;
    player.x = screenWidth - player.width - 10;
    player.y = screenHeight / 2 - player.height / 2;
    player.speed = 7;

    computer.width = 20;
    computer.height = 120;
    computer.x = 10;
    computer.y = screenHeight / 2 - player.height / 2;
    computer.speed = 7;

    InitWindow(screenWidth, screenHeight, "Pong");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);

        ball.Draw();
        ball.Update();

        player.Draw();
        player.Update();

        computer.Draw();
        computer.Update(ball.y); 

        DrawText(TextFormat("%d", playerScore), screenWidth / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%d", computerScore), 3 * screenWidth / 4 - 20, 20, 80, WHITE);

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speedX *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{computer.x, computer.y, computer.width, computer.height}))
        {
            ball.speedX *= -1;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}