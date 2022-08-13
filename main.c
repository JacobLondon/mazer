#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <raylib/raylib.h>
#include <raylib/raygui.h>
#include "mazer.h"
#include "util.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    srand(time(NULL));

    const size_t ROWS = 24;
    const size_t COLS = 40;
    const size_t SQUARE = 10;

    Mazer *m = MazerNew(ROWS, COLS);
    OK_OR_RETURN(m, 1);
    //MazerPrint(m);

    InitWindow(1200, 720, "Mazer");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (size_t i = 0; i < MazerRows(m); i++) {
            for (size_t j = 0; j < MazerColumns(m); j++) {
                if (MazerIsSolid(m, i, j)) {
                    DrawRectangle(j*SQUARE, i*SQUARE, SQUARE, SQUARE, BLACK);
                }
            }
        }
        EndDrawing();

        if (IsKeyPressed(KEY_R))
        {
            MazerDelete(m);
            m = MazerNew(ROWS, COLS);
            OK_OR_RETURN(m, 1);
        }
    }
    CloseWindow();

    MazerDelete(m);

    return 0;
}
