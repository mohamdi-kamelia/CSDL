#include <raylib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "constants.hpp"


typedef enum GameScreen {menu, game, save, load} GameScreen; // Define the different screens of the game


// Function to count alive neighbors of a cell
int countLiveNeighbors(bool grid[][cols], int x, int y) {
    int count = 0;

    // Check if the cell is on the border, if so return 0
    if (x == rows - 1 || y == cols - 1) {
        return count;
    }

    // Check the 8 neighbors of the cell and returns the number of alive neighbors
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
            // Calculate the number of live neighbors
            int liveNeighbors = countLiveNeighbors(currentGen, i, j);

            // Apply the rules based on the number of live neighbors
            if (currentGen[i][j]) {
                nextGen[i][j] = (liveNeighbors == 2 || liveNeighbors == 3);
            } else {
                nextGen[i][j] = (liveNeighbors == 3);
            }
        }
    }
}

// Function to save the current population to a file and add the filename to saves.txt
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
    
    std::ofstream file2("saves.txt", std::ios::app);
    if (!file2.is_open()) {
    std::cerr << "Error: could not open file " << "saves.txt" << std::endl;
    }
    else {
    file2 << filename << std::endl;
    file2.close();
    }
}

// Function to load a population from a file
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
            std::cout << currentGen[i][j];
        }
    }
    file.close();
    std::cout << "Population loaded from file " << filename << std::endl;
}

// Function to generate a random population
void randomGeneration(bool currentGen[][cols]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            currentGen[i][j] = (GetRandomValue(0, 1) == 1);
        }
    }
}

int main(int argc, char* argv[])
{
    Color darkGreen = Color{20, 160, 133, 255};
    Color white = Color{255, 255, 255, 255};

    Font GetFontDefault(void);

    GameScreen currentScreen = menu;
    
    InitWindow(screenWidth, screenHeight, "Game of life");
    SetTargetFPS(60);

    // Initialize the grid with the default pattern
    bool currentGen[rows][cols] = { false };
    bool nextGen[rows][cols] = { false };
    
    currentGen[59][59] = true;
    currentGen[59][60] = true;
    currentGen[59][61] = true;
    currentGen[60][59] = true;
    currentGen[60][61] = true;
    currentGen[61][59] = true;
    currentGen[61][61] = true;

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
                DrawText("Lancer",200, 100, 50, white);
                DrawText("Générer population aléatoire", 200, 225, 50, white);
                DrawText("Lancement population par défaut", 200, 350, 50, white);
                DrawText("Sauvegarder Population actuelle", 200, 475, 50, white);
                DrawText("Charger Population", 200, 600, 50, white);

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& GetMousePosition().x > buttonX && GetMousePosition().x < buttonWidth){
                    if (GetMousePosition().y > 75 && GetMousePosition().y < (75 + buttonHeight))
                    {
                        currentScreen = game;
                    }
                    if (GetMousePosition().y > 200 && GetMousePosition().y < (200 + buttonHeight))
                    {
                        randomGeneration(currentGen);
                        currentScreen = game;
                    }
                    if (GetMousePosition().y > 325 && GetMousePosition().y < (325 + buttonHeight))
                    {
                        loadPopulation(currentGen, "default.txt");
                        currentScreen = game;
                    }
                    if (GetMousePosition().y > 450 && GetMousePosition().y < (450 + buttonHeight))
                    {
                        currentScreen = save;
                    }
                    if (GetMousePosition().y > 575 && GetMousePosition().y < (575 + buttonHeight))
                    {
                        currentScreen = load;
                    }
                }
            } break;

            case game:
            {
                SetTargetFPS(10); // Slow down the game to make it more visible
                ClearBackground(darkGreen); // Clear the screen

                // We use an offset to only display the center of the grid, the grid is 120x120 and we only display 30x40
                int rowOffset = 45;
                int colOffset = 40;

                // Display the grid
                for (int i = rowOffset; i < rowOffset + 30; ++i) {
                    for (int j = colOffset; j < colOffset + 40; ++j) {
                        if (currentGen[i][j]) {
                            DrawRectangle((j - colOffset) * cellSize, (i - rowOffset) * cellSize, cellSize, cellSize, WHITE);
                        }
                        else {
                            DrawRectangleLines((j - colOffset) * cellSize, (i - rowOffset) * cellSize, cellSize, cellSize, WHITE);
                        }
                    }
                }
                
                // Apply the rules to create the next generation
                applyRules(currentGen, nextGen);
                std::swap(currentGen, nextGen);

                // Check if the user wants to go back to the menu
                if (IsKeyPressed(KEY_SPACE))
                {
                    currentScreen = menu;
                }
            } break;

            case save:
            {
                static std::string populationName;
                int key = GetCharPressed(); // Get the key pressed by the user

                DrawText("Entrez le nom de la population : ", 200, 775, 50, white);

                DrawRectangleLines(buttonX, 875, buttonWidth, buttonHeight, white);
                DrawText(populationName.c_str(), 200, 900, 50, white);

                DrawRectangleLines(buttonX, 1000, buttonWidth, buttonHeight, white);
                DrawText("Valider", 200, 1025, 50, white);
                
                if (key >= 32 && key <= 125) // Check if the key is a printable character                    
                {
                    // Convert the key to a char and add it to the population name
                    char character = static_cast<char>(key);
                    populationName += character;
                }
                
                // Check if the backspace key is pressed and remove the last character from the population name
                if (IsKeyPressed(KEY_BACKSPACE) && !populationName.empty())
                {
                    populationName.pop_back();                        
                }
                
                DrawRectangle(200, 900, 800, 50, darkGreen);
                DrawText(populationName.c_str(), 200, 900, 50, white);
                
                // If the user clicks on the validate button or presses enter, save the population and return to the menu
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& GetMousePosition().x > buttonX && GetMousePosition().x < buttonWidth && GetMousePosition().y > 1025 && GetMousePosition().y < (1025 +buttonHeight)) || IsKeyPressed(KEY_ENTER))
                {
                    saveCurrentPopulation(currentGen, populationName + ".txt");
                    currentScreen = menu;
                }                
            } break;

            case load:
            {
                ClearBackground(darkGreen);

                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        currentGen[i][j] = false;
                    }
                }

                // Read the save files from saves.txt
                std::ifstream file("saves.txt");
                if (!file.is_open()) {
                    std::cerr << "Error: could not open file saves.txt" << std::endl;
                }
                std::vector<std::string> saveFiles; // Store the filenames from saves.txt
                std::string line;
                while (std::getline(file, line)) {
                    saveFiles.push_back(line);
                }
                file.close();

                // Display buttons for each save file
                for (size_t i = 0; i < saveFiles.size(); ++i) {
                    DrawRectangleLines(buttonX, 75 + i * 125, buttonWidth, buttonHeight, white);
                    DrawText(saveFiles[i].c_str(), 200, 100 + i * 125, 50, white);
                    // Check if a button is clicked and load the corresponding file
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMousePosition().x > buttonX && GetMousePosition().x < buttonWidth && GetMousePosition().y > 75 + i * 125 && GetMousePosition().y < (75 + buttonHeight + i * 125)) {
                        loadPopulation(currentGen, saveFiles[i]);
                        currentScreen = menu; // Return to menu after loading
                    }
                }
            }
        }


    EndDrawing();
    }

    CloseWindow();
    return 0;
}