#include "raylib.h"

int main()
{
    //rozmiar okna
    int windowWidth{512};
    int windowHeight{380};
   
    InitWindow(windowWidth, windowHeight, "Jumper");

    const int width{50};
    const int height{80};

    int posY{windowHeight - height};
    int velocity{0};

    const int gravity{1};
    const int jumpVel{-17};

    bool isInAir{};
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
                
        
        if (posY >= windowHeight - height)
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            velocity += gravity;
            isInAir = true;
        }
        
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }
        posY += velocity;

        DrawRectangle(windowWidth/2, posY, width, height, BLUE);
        EndDrawing();
    }
    CloseWindow();
    
}