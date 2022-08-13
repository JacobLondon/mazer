#include <assert.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <stdbool.h>
#include "mazer.h"

static int MazerRandom(int most)
{
    static int last = 0;
    return ((last += (rand()*0x01000193)) % most);
}

typedef enum
{
    MazerNONE  = 0x0,
    MazerNORTH = 0x1,
    MazerEAST  = 0x2,
    MazerSOUTH = 0x4,
    MazerWEST  = 0x8,
} MazerPathEnum;

typedef struct
{
    int taken;
} MazerPathStruct;

static void MazerPathChooserInit(MazerPathStruct *mpc, int taken)
{
    assert(mpc != NULL);
    memset(mpc, 0, sizeof(*mpc));
    mpc->taken = taken;
}

static int MazerPathFill(MazerPathStruct *mpc, MazerPathEnum options[4])
{
    assert(mpc != NULL);
    assert(options != NULL);

    int count = 0;
    if (!(MazerNORTH & mpc->taken)) {
        options[count++] = MazerNORTH;
    }
    if (!(MazerEAST & mpc->taken)) {
        options[count++] = MazerEAST;
    }
    if (!(MazerSOUTH & mpc->taken)) {
        options[count++] = MazerSOUTH;
    }
    if (!(MazerWEST & mpc->taken)) {
        options[count++] = MazerWEST;
    }
    return count;
}

static MazerPathEnum MazerPathChoose(MazerPathStruct *mpc)
{
    assert(mpc != NULL);
    MazerPathEnum options[4];
    memset(options, 0, sizeof(options));

    const int count = MazerPathFill(mpc, options);
    if (count == 0) return MazerNONE;

    const int choice = MazerRandom(count);
    mpc->taken |= options[choice];
    return options[choice];
}

static int MazerPathCount(MazerPathStruct *mpc)
{
    assert(mpc != NULL);
    int count = 0;
    count += !!(MazerNORTH & mpc->taken);
    count += !!(MazerEAST  & mpc->taken);
    count += !!(MazerSOUTH & mpc->taken);
    count += !!(MazerWEST  & mpc->taken);
    return count;
}

typedef struct
{
    bool visited;
    unsigned char path;
} MazerCell;

struct Mazer
{
    size_t rows, columns;
    MazerCell *cells;
};

static bool MazerInBounds(Mazer *m, size_t row, size_t column)
{
    assert(m != NULL);
    return ((row < m->rows) && (column < m->columns));
}

static MazerCell *MazerGet(Mazer *m, size_t i, size_t j)
{
    assert(MazerInBounds(m, i, j));
    return &m->cells[(i * m->columns) + j];
}

static bool MazerRecurse(Mazer *m, size_t i, size_t j, MazerPathEnum direction_to_previous)
{
    // this cell in not reachable
    if (!MazerInBounds(m, i, j)) return false;

    MazerCell *c = MazerGet(m, i, j);
    if (c->visited) return false; // No loops!

    // before so we don't loop between two adjacent forever
    c->visited = true;
    c->path |= direction_to_previous;

    MazerPathStruct chooser;
    MazerPathChooserInit(&chooser, direction_to_previous);
    int choice;
    for (choice = MazerPathChoose(&chooser);
         choice != MazerNONE;
         choice = MazerPathChoose(&chooser))
    {
        // cap on the number of paths from a cell
        if (MazerPathCount(&chooser) > 4) break;

        bool found = false;
        switch (choice)
        {
        case MazerNONE:
            break;
        case MazerNORTH:
            found = MazerRecurse(m, i-1, j, MazerSOUTH);
            break;
        case MazerEAST:
            found = MazerRecurse(m, i, j+1, MazerWEST);
            break;
        case MazerSOUTH:
            found = MazerRecurse(m, i+1, j, MazerNORTH);
            break;
        case MazerWEST:
            found = MazerRecurse(m, i, j-1, MazerEAST);
            break;
        }

        if (found) {
            c->path |= choice;
        }
    }

    // this cell must have been reachable
    return true;
}

Mazer *MazerNew(size_t rows, size_t columns)
{
    // create an empty mazer
    Mazer *m = malloc(sizeof(Mazer));
    if (!m) {
        return NULL;
    }
    memset(m, 0, sizeof(*m));
    m->rows = rows;
    m->columns = columns;

    size_t size = rows * columns * sizeof(MazerCell);
    m->cells = malloc(size);
    if (!m) {
        free(m);
        return NULL;
    }
    memset(m->cells, 0, size);

    // fill it
    (void)MazerRecurse(m, rows/2, columns/2, MazerNONE);

    return m;
}

void MazerDelete(Mazer *m)
{
    if (!m) return;
    if (m->cells)
    {
        free(m->cells);
    }
    memset(m, 0, sizeof(*m));
    free(m);
}

bool MazerIsSolid(Mazer *m, size_t row, size_t column)
{
    assert(m != NULL);
    assert(row < MazerRows(m));
    assert(column < MazerColumns(m));

    size_t major_row = row / 3;
    size_t minor_row = row % 3;
    size_t major_col = column / 3;
    size_t minor_col = column % 3;

    MazerCell *c = MazerGet(m, major_row, major_col);
    int path = c->path;
    if (minor_row == 0) {
        if (path & MazerNORTH) {
            return ("# #"[minor_col] == '#');
        }
        return true;
    }
    else if (minor_row == 1) {
        if ((path & MazerEAST) &&
            (path & MazerWEST))
        {
            return false;
        }
        else if (path & MazerEAST) {
            return ("#  "[minor_col] == '#');
        }
        else if (path & MazerWEST) {
            return ("  #"[minor_col] == '#');
        }
        else if (path & (MazerNORTH|MazerSOUTH)) {
            return ("# #"[minor_col] == '#');
        }
        return true;
    }
    else { // if (minor_row == 2) {
        if (path & MazerSOUTH) {
            return ("# #"[minor_col] == '#');
        }
        return true;
    }
}

void MazerPrint(Mazer *m)
{
    assert(m != NULL);

    size_t i, j;
    for (i = 0; i < MazerRows(m); i++) {
        for (j = 0; j < MazerColumns(m); j++) {
            if (MazerIsSolid(m, i, j)) {
                printf("#");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

size_t MazerRows(Mazer *m)
{
    assert(m != NULL);
    return m->rows * 3;
}

size_t MazerColumns(Mazer *m)
{
    assert(m != NULL);
    return m->columns * 3;
}
