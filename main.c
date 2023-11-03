#include "include/raylib.h"
#include <stdbool.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(void)
{
    bool gameRunning = false;
    bool blueWin = false;
    bool redWin = false;
    int bluePoints = 0;
    int redPoints = 0;

    struct Player
    {
        Vector2 position;
        float speed;
        Vector2 size;
        Color color;
    };

    struct Ball
    {
        Vector2 position;
        Vector2 speed;
        float size;
        Color color;
    };

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");

    SetTargetFPS(60);

    struct Player redPlayer = { {20.f, SCREEN_HEIGHT / 2.0f }, 5.0f, { 10.0f, 100.0f }, RED };
    struct Player bluePlayer = { { SCREEN_WIDTH - 20.0f, SCREEN_HEIGHT / 2.0f }, 5.0f, { 10.0f, 100.0f }, BLUE };
    struct Ball ball1 = { { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f }, {6.0f, 6.0f}, 9.0f, GREEN };

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        if (gameRunning) // condition to make the ball move and update score
        {
            ball1.position.x += ball1.speed.x; // make the ball move based on speed, initially going right + down
            ball1.position.y += ball1.speed.y;

            if (ball1.position.x <= 0) // if ball get out of screen to the left
            {
                gameRunning = false;
                blueWin = true;
                bluePoints++;
            }

            if (ball1.position.x >= SCREEN_WIDTH) // if ball get out of screen to the right
            {
                gameRunning = false;
                redWin = true;
                redPoints++;
            }
        }

        if (IsKeyDown(KEY_W)) redPlayer.position.y -= redPlayer.speed; // W and S to control redPlayer
        if (IsKeyDown(KEY_S)) redPlayer.position.y += redPlayer.speed;
        if (IsKeyDown(KEY_UP)) bluePlayer.position.y -= redPlayer.speed; // up and down arrow keys to control redPlayer
        if (IsKeyDown(KEY_DOWN)) bluePlayer.position.y += redPlayer.speed;

        if (redPlayer.position.y >= SCREEN_HEIGHT - redPlayer.size.y) redPlayer.position.y -= redPlayer.speed; // if redPlayer go out the screen set his pos back
        if (redPlayer.position.y <= 0.0f) redPlayer.position.y += redPlayer.speed;

        if (bluePlayer.position.y >= SCREEN_HEIGHT - bluePlayer.size.y) bluePlayer.position.y -= bluePlayer.speed; // if bluePlayer go out the screen set his pos back
        if (bluePlayer.position.y <= 0.0f) bluePlayer.position.y += bluePlayer.speed;

        if (ball1.position.y >= SCREEN_HEIGHT - ball1.size || ball1.position.y <= 0.0f) // ball to wall vertical collision
        {
            ball1.speed.y *= -1;
        }

        if (ball1.position.x <= (redPlayer.position.x + redPlayer.size.x) && ball1.position.x >= redPlayer.position.x) // ball collision to redPlayer horizontal hitbox
        {
            if (ball1.position.y >= redPlayer.position.y && ball1.position.y <= redPlayer.position.y + redPlayer.size.y) // ball collision to redPlayer vertical hitbox
            {
                if ((IsKeyDown(KEY_W) && ball1.speed.y > 0.0f) || (IsKeyDown(KEY_S) && ball1.speed.y < 0.0f)) // invert ball vertical direction if redPlayer is against ball vertical direction
                {
                    ball1.speed.y *= -1.0f;
                }
                ball1.speed.x *= -1;
            }
        }

        if (ball1.position.x >= bluePlayer.position.x && ball1.position.x <= (bluePlayer.position.x + bluePlayer.size.x)) // ball collision to bluePlayer horizontal hitbox
        {
            if (ball1.position.y >= bluePlayer.position.y && ball1.position.y <= (bluePlayer.position.y + bluePlayer.size.y)) // ball collision to bluePlayer vertical hitbox
            {
                if ((IsKeyDown(KEY_UP) && ball1.speed.y > 0.0f) || (IsKeyDown(KEY_DOWN) && ball1.speed.y < 0.0f)) // invert ball vertical direction if bluePlayer is against ball vertical direction
                {
                    ball1.speed.y *= -1.0f;
                }
                ball1.speed.x *= -1;
            }
        }

        BeginDrawing();

            ClearBackground(BLACK); // clear background with black color after each frame

            if (gameRunning == false)
            {
                if(blueWin)
                {
                    DrawText("BLUE WINS!", SCREEN_WIDTH / 2 - 105, SCREEN_HEIGHT / 2 - 100, 40, BLUE);
                }

                if(redWin)
                {
                    DrawText("RED  WINS!", SCREEN_WIDTH / 2 - 105, SCREEN_HEIGHT / 2 - 100, 40, RED);
                }
                DrawText("Press R to start the game", SCREEN_WIDTH / 2 - 130, SCREEN_HEIGHT / 2 + 100, 20, GREEN);

                if(IsKeyPressed(KEY_R))
                {
                    gameRunning = true;
                    blueWin = false;
                    redWin = false;
                    ball1.position.x = SCREEN_WIDTH / 2;
                    ball1.position.y = SCREEN_HEIGHT / 2;
                    redPlayer.position.y = SCREEN_HEIGHT / 2;
                    bluePlayer.position.y = SCREEN_HEIGHT / 2;
                }
            }

            DrawText(TextFormat("BLUE: %d", bluePoints), 500, 0, 30, BLUE);
            DrawText(TextFormat("RED: %d", redPoints), 200, 0, 30, RED);
            DrawRectangleV(redPlayer.position, redPlayer.size, redPlayer.color);
            DrawRectangle(SCREEN_WIDTH / 2, 0, 1, SCREEN_HEIGHT, WHITE); // middle line
            DrawRectangleV(bluePlayer.position, bluePlayer.size, bluePlayer.color);
            DrawCircleV(ball1.position, ball1.size, ball1.color);
            
        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
