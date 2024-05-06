#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int rows = 30; // Nombre de lignes
    const int cols = 40; // Nombre de colonnes
    const int cellSize = 20; // Taille de chaque cellule

    // Initialisation de la fenêtre raylib
    InitWindow(screenWidth, screenHeight, "Grille de cellules");

    SetTargetFPS(60); // Définit le framerate de la fenêtre

    // Boucle principale du jeu
    while (!WindowShouldClose()) {
        // Début du dessin
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Dessin de la grille de cellules
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                DrawRectangle(j * cellSize, i * cellSize, cellSize, cellSize, LIGHTGRAY);
                DrawRectangleLines(j * cellSize, i * cellSize, cellSize, cellSize, GRAY);
            }
        }

        EndDrawing();
    }

    // Fermeture de la fenêtre raylib
    CloseWindow();

    return 0;
}
