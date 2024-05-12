#include <raylib.h>
#include <iostream>
#include "menu.hpp"
#include <fstream>

typedef enum GameScreen {menu, game, save} GameScreen;

const int screenWidth = 1600;
const int screenHeight = 900;

// Function to count alive neighbors of a cell
int countLiveNeighbors(bool grid[][cols], int x, int y) {
    int count = 0;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int neighborX = x + i;
            int neighborY = y + j;

            if (grid[neighborX][neighborY]) {
                count++;
            }
        }
    }
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
            // Otherwise, apply rules
            int liveNeighbors = countLiveNeighbors(currentGen, i, j);
            if (currentGen[i][j]) {
                nextGen[i][j] = (liveNeighbors == 2 || liveNeighbors == 3);
            } else {
                nextGen[i][j] = (liveNeighbors == 3);
            }
            }
        }
    }
}

void saveCurrentPopulation(bool currentGen[][cols], std::string filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file << currentGen[i][j];
        }
        file << std::endl;
    }
    file.close();
    std::cout << "Population saved to file " << filename << std::endl;
}

void loadPopulation(bool currentGen[][cols], std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char cell;
            file >> cell;
            currentGen[i][j] = (cell == '1');
        }
    }
    file.close();
    std::cout << "Population loaded from file " << filename << std::endl;
}

int main(int argc, char* argv[])
{
    Color darkGreen = Color{20, 160, 133, 255};
    Color white = Color{255, 255, 255, 255};



    Font GetFontDefault(void);

    GameScreen currentScreen = menu;
    
    InitWindow(screenWidth, screenHeight, "Game of life");
    SetTargetFPS(60);

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
                DrawRectangleLines(buttonX, 575, buttonWidth, buttonHeight, white);
                DrawText("Lancer le jeu",200, 100, 50, white);
                DrawText("Générer population aléatoire", 200, 225, 50, white);
                DrawText("Lancement population par défaut", 200, 350, 50, white);
                DrawText("Sauvegarder Population courante", 200, 475, 50, white);
                DrawText("Charger Population", 200, 600, 50, white);

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& GetMousePosition().x > buttonX && GetMousePosition().x < buttonWidth && GetMousePosition().y > 75 && GetMousePosition().y < (75 +buttonHeight))
                {
                    currentScreen = game;
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& GetMousePosition().x > buttonX && GetMousePosition().x < buttonWidth && GetMousePosition().y > 450 && GetMousePosition().y < (450 +buttonHeight))
                {                        
                    currentScreen = save;               
                }

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& GetMousePosition().x > buttonX && GetMousePosition().x < buttonWidth && GetMousePosition().y > 575 && GetMousePosition().y < (575 +buttonHeight))
                {
                    loadPopulation(currentGen, "population.txt");
                } 

            } break;

            case game:
            {
                SetTargetFPS(10);
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


                if (IsKeyPressed(KEY_SPACE))
                {
                    currentScreen = menu;
                }
            } break;

            case save:
                static std::string populationName;
                int key = GetCharPressed();

                DrawText("Entrez le nom de la population : ", 200, 775, 50, white);

                DrawRectangleLines(buttonX, 875, buttonWidth, buttonHeight, white);
                DrawText(populationName.c_str(), 200, 900, 50, white);

                DrawRectangleLines(buttonX, 1000, buttonWidth, buttonHeight, white);
                DrawText("Valider", 200, 1025, 50, white);
                
                if (key >= 32 && key <= 125)                    
                {
                    char character = static_cast<char>(key);
                    populationName += character;
                }
                
                if (IsKeyPressed(KEY_BACKSPACE) && !populationName.empty())
                {
                    populationName.pop_back();                        
                }
                
                DrawRectangle(200, 900, 800, 50, darkGreen);
                DrawText(populationName.c_str(), 200, 900, 50, white);
                
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& GetMousePosition().x > buttonX && GetMousePosition().x < buttonWidth && GetMousePosition().y > 1025 && GetMousePosition().y < (1025 +buttonHeight)) || IsKeyPressed(KEY_ENTER))
                {
                    saveCurrentPopulation(currentGen, populationName + ".txt");
                    currentScreen = menu;
                } break;                
    }


    EndDrawing();
    }

    CloseWindow();
    return 0;
}