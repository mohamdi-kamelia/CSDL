#include <raylib.h>
#include <iostream>
#include "menu.hpp"
#include <thread>
#include <chrono>

typedef enum GameScreen {menu, game} GameScreen;

const int screenWidth = 1600;
const int screenHeight = 1200;

// Function to count alive neighbors of a cell
int countLiveNeighbors(bool grid[][cols], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            // Calculate neighbor position with wrapping
            int neighborX = x + i;
            int neighborY = y + j;
            // Check if neighbor is alive
            if (grid[neighborX][neighborY]) {

                count++;
            }
        }
    }
    // Exclude the current cell
    if (grid[x][y]) {
        count--;
    }
    return count;
}

// Function to apply the rules and generate the next grid
void applyRules(bool currentGen[][cols], bool nextGen[][cols]) {
    for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
        // Calculate the position of the cell in screen coordinates
        int posX = j * cellSize;
        int posY = i * cellSize;

        // Check if the cell is outside the bounds of the screen
        if (posX < 0 || posX >= screenWidth || posY < 0 || posY >= screenHeight) {
            nextGen[i][j] = false; // Set the cell to dead
        } else {
            // Otherwise, apply Conway's rules as usual
            int liveNeighbors = countLiveNeighbors(currentGen, i, j);
            if (currentGen[i][j]) {
                // Any live cell with fewer than two live neighbors dies
                // Any live cell with more than three live neighbors dies
                nextGen[i][j] = (liveNeighbors == 2 || liveNeighbors == 3);
            } else {
                // Any dead cell with exactly three live neighbors becomes a live cell
                nextGen[i][j] = (liveNeighbors == 3);
            }
        }
    }
}
}

int main()
{
    Color darkGreen = Color{20, 160, 133, 255};
    Color white = Color{255, 255, 255, 255};



    Font GetFontDefault(void);

    GameScreen currentScreen = menu;
    
    InitWindow(screenWidth, screenHeight, "Game of life");
    SetTargetFPS(120);

    bool currentGen[rows][cols] = { false };
    bool nextGen[rows][cols] = { false };    

    // Initialize the grid with a glider gun pattern
    currentGen[11][25] = true;
    currentGen[12][23] = true;
    currentGen[12][25] = true;
    currentGen[13][13] = true;
    currentGen[13][14] = true;
    currentGen[13][21] = true;
    currentGen[13][22] = true;
    currentGen[13][35] = true;
    currentGen[13][36] = true;
    currentGen[14][12] = true;
    currentGen[14][16] = true;
    currentGen[14][21] = true;
    currentGen[14][22] = true;
    currentGen[14][35] = true;
    currentGen[14][36] = true;
    currentGen[15][1] = true;
    currentGen[15][2] = true;
    currentGen[15][11] = true;
    currentGen[15][17] = true;
    currentGen[15][21] = true;
    currentGen[15][22] = true;
    currentGen[16][1] = true;
    currentGen[16][2] = true;
    currentGen[16][11] = true;
    currentGen[16][15] = true;
    currentGen[16][17] = true;
    currentGen[16][18] = true;
    currentGen[16][23] = true;
    currentGen[16][25] = true;
    currentGen[17][11] = true;
    currentGen[17][17] = true;
    currentGen[17][25] = true;
    currentGen[18][12] = true;
    currentGen[18][16] = true;
    currentGen[19][13] = true;
    currentGen[19][14] = true;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        switch (currentScreen)
        {
            case menu:
            {                
                ClearBackground(darkGreen);
                DrawRectangleLines(buttonX, 75, buttonWidth, buttonHeight, white);
                DrawRectangleLines(buttonX, 200, buttonWidth, buttonHeight, white);
                DrawRectangleLines(buttonX, 325, buttonWidth, buttonHeight, white);
                DrawRectangleLines(buttonX, 450, buttonWidth, buttonHeight, white);
                DrawText("Lancer le jeu",200, 100, 50, white);
                DrawText("Générer population aléatoire", 200, 225, 50, white);
                DrawText("Lancement population par défaut", 200, 350, 50, white);
                DrawText("Sauvegarder Population courante", 200, 475, 50, white);

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& GetMousePosition().x > buttonX && GetMousePosition().x < buttonWidth && GetMousePosition().y > 75 && GetMousePosition().y < (75 +buttonHeight))
                {
                    currentScreen = game;
                }
            } break;
            case game:
            {
                ClearBackground(darkGreen);

                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        if (currentGen[i][j]) {
                            DrawRectangle(j * cellSize, i * cellSize, cellSize, cellSize, WHITE);
                        }
                        else {
                            DrawRectangleLines(j * cellSize, i * cellSize, cellSize, cellSize, WHITE);
                        }
                    }
                }

                applyRules(currentGen, nextGen);

                std::swap(currentGen, nextGen);

                //std::this_thread::sleep_for(std::chrono::milliseconds(200));


                if (IsKeyPressed(KEY_SPACE))
                {
                    currentScreen = menu;
                }
            } break;                
    }


    EndDrawing();
    }

    CloseWindow();
    return 0;
}