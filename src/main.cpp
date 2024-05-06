#include <raylib.h>
#include <iostream>
#include "menu.hpp"

int main()
{
    Color darkGreen = Color{20, 160, 133, 255};
    Color white = Color{255, 255, 255, 255};

    const int screenWidth = 1600;
    const int screenHeight = 1200;

    Font GetFontDefault(void);
    
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkGreen);
        DrawRectangleLines(buttonX, 75, buttonWidth, buttonHeight, white);
        DrawRectangleLines(buttonX, 200, buttonWidth, buttonHeight, white);
        DrawRectangleLines(buttonX, 325, buttonWidth, buttonHeight, white);
        DrawRectangleLines(buttonX, 450, buttonWidth, buttonHeight, white);
        DrawText("Lancer le jeu",200, 100, 50, white);
        DrawText("Générer population aléatoire", 200, 225, 50, white);
        DrawText("Lancement population par défaut", 200, 350, 50, white);
        DrawText("Sauvegarder Population courante", 200, 475, 50, white);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& GetMousePosition().x > 100 && GetMousePosition().x < 700 && GetMousePosition().y > 75 && GetMousePosition().y < 175)
        {
            DrawRectangle(100, 200, 600, 100, white);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}