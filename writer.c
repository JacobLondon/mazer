#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <stdio.h>
#include <raylib/raylib.h>
#include <raylib/raygui.h>
#include "util.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    InitWindow(800, 300, "Writer");
    SetTargetFPS(120);
    //SetWindowOpacity(0.5);

    Font deja_vu_sans_mono = LoadFont("wgd/fonts/DejaVuSansMono.ttf");

    size_t LEN = 30*80;
    char *buffer = malloc(LEN*sizeof(char));
    if (!buffer) return 1;
    memset(buffer, 0, LEN*sizeof(char));
    ssize_t ndx = 0;

    char line[81];

    int ch;
    while (!WindowShouldClose()) {
        for (ch = GetCharPressed();
             ch > 0;
             ch = GetCharPressed())
        {
            if  ((ch >= 32) && (ch <= 126)) {
                buffer[ndx] = (char)ch;
                ndx = (ndx + 1) % LEN;
            }
            else {
                printf("%d\n", ch);
            }
        }

        if (IsKeyDown(KEY_LEFT_CONTROL))
        {
            //if 
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            buffer[ndx] = '\n';
            ndx = (ndx + 1) % LEN;
        }
        else if (IsKeyPressed(KEY_BACKSPACE))
        {
            ndx = (ndx - 1) % LEN;
            if (ndx < 0)
                ndx = LEN + ndx;
            buffer[ndx] = 0;
        }
        memcpy(line, buffer, sizeof(line)-1);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(deja_vu_sans_mono, line, (Vector2){5, 5}, 20, 0, RAYWHITE);
        EndDrawing();
    }
    UnloadFont(deja_vu_sans_mono);
    CloseWindow();

    return 0;
}
