#ifndef MAZER_H_
#define MAZER_H_

#include <stddef.h>

typedef struct Mazer Mazer;

Mazer *MazerNew(size_t rows, size_t columns);
void MazerDelete(Mazer *m);
bool MazerIsSolid(Mazer *m, size_t row, size_t column);
void MazerPrint(Mazer *m);
size_t MazerRows(Mazer *m);
size_t MazerColumns(Mazer *m);

#endif // MAZER_H_
