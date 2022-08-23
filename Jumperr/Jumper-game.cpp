#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;
      
    InitWindow(windowDimensions[0], windowDimensions[1], "Jumper");

    int velocity{0};

    const int gravity{1'000};
    const int jumpVel{-600};
    
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
        
    const int sizeOfNebulae{10};

    AnimData nebulae[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
        nebulae[i].pos.x = windowDimensions[0] + i * 300;
    } 

    int nebVel{-200};
    
    Texture2D character = LoadTexture("textures/character.png");
    AnimData characterData;
    characterData.rec.width = character.width/6;
    characterData.rec.height = character.height;
    characterData.rec.x = 0;
    characterData.rec.y = 0;
    characterData.pos.x = windowDimensions[0]/2 - characterData.rec.width/2;
    characterData.pos.y = windowDimensions[1] - characterData.rec.height;
    characterData.frame = 0;
    characterData.updateTime = 1.0/12.0;
    characterData.runningTime = 0.0;

    bool isInAir{};
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        const float dT{GetFrameTime()};
        
        BeginDrawing();
        ClearBackground(WHITE);
                
        
        if (characterData.pos.y >= windowDimensions[1] - characterData.rec.height)
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            velocity += gravity * dT;
            isInAir = true;
        }
        
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }
        //pos update
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].pos.x += nebVel * dT;
        }

        characterData.pos.y += velocity * dT;
        //
        if (!isInAir)
        {
            characterData.runningTime += dT;
            if (characterData.runningTime >= characterData.updateTime)
            {
                characterData.runningTime = 0.0;
                characterData.rec.x = characterData.frame * characterData.rec.width;
                characterData.frame++;
                if (characterData.frame > 5)
                {
                    characterData.frame = 0;
                }
            }
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].runningTime += dT;
            if (nebulae[i].runningTime >= nebulae[i].updateTime)
            {
                nebulae[i].runningTime = 0.0;
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                if (nebulae[i].frame > 7)
                {
                    nebulae[i].frame = 0;
                }
            }
        }
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }
        
        DrawTextureRec(character, characterData.rec, characterData.pos, WHITE);
        EndDrawing();
    }

    UnloadTexture(character);
    UnloadTexture(nebula);
    CloseWindow();
    
}