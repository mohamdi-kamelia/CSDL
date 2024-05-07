#include "raylib.h"

#define rows 30
#define cols 40
#define cellSize 20

bool grid[rows][cols] = {0}; // grille de cellules

// Fonction pour initialiser l'état initial de la grille
void initGrid(int numAliveCells) {
    while (numAliveCells--) {
        int x = GetRandomValue(0, cols - 1);
        int y = GetRandomValue(0, rows - 1);
        grid[y][x] = true;
    }
}

// Fonction pour calculer l'état suivant de la grille en fonction des règles
void updateGrid() {
    bool nextGrid[rows][cols] = {0};

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int aliveNeighbors = 0;

            for (int ni = -1; ni <= 1; ++ni) {
                for (int nj = -1; nj <= 1; ++nj) {
                    if (ni == 0 && nj == 0) continue; // ignore la cellule elle-même

                    int x = j + nj;
                    int y = i + ni;

                    if (x >= 0 && x < cols && y >= 0 && y < rows && grid[y][x]) {
                        aliveNeighbors++;
                    }
                }
            }

            if (grid[i][j]) {
                // Règle de stase ou de morte
                nextGrid[i][j] = (aliveNeighbors == 2 || aliveNeighbors == 3);
            } else {
                // Règle de naissance
                nextGrid[i][j] = (aliveNeighbors == 3);
            }
        }
    }

    // Copie le prochain état de la grille dans la grille actuelle
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = nextGrid[i][j];
        }
    }
}

int main() {
    const int screenWidth = cols * cellSize;
    const int screenHeight = rows * cellSize;

    InitWindow(screenWidth, screenHeight, "Jeu de la vie de Conway");

    SetTargetFPS(10);

    // Initialisation de l'état initial de la grille avec 150 cellules vivantes
    initGrid(150);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Dessin de la grille
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j]) {
                    DrawRectangle(j * cellSize, i * cellSize, cellSize, cellSize, BLACK);
                } else {
                    DrawRectangleLines(j * cellSize, i * cellSize, cellSize, cellSize, GRAY);
                }
            }
        }

        // Met à jour la grille
        updateGrid();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
