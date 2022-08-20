#ifndef HKMN_MOVE_H_
#define HKMN_MOVE_H_

#include <stdbool.h>
#include <stddef.h>
#include "hkmn.h"
#include "hkmn_env.h"
#include "hkmn_types.h"

#define HkmnMoveARGS HkmnMove *h_self, HkmnEnvironment *h_env, Hkmn *h_us[], size_t h_uscount, Hkmn *h_them[], size_t h_themcount
#define HkmnMoveARGS_OK() \
do { \
    assert(h_self); \
    assert(h_env); \
    assert(h_us); \
    assert(h_uscount > 0); \
    assert(h_them); \
    assert(h_themcount > 0); \
} while (0)

typedef void (* HkmnMoveOperationFunc)(HkmnMoveARGS);

typedef struct HkmnMoveDefinition
{
    const char *name;
    HkmnLocationEnum location;
    HkmnEnvEnum env;
    HkmnTypeEnum type;
    HkmnMoveOperationFunc move;
    int pp;
    float power;
    float accuracy;
} HkmnMoveDefinition;

typedef struct HkmnMove HkmnMove;

HkmnMove *HkmnMoveNew(HkmnMoveDefinition *definition);
void HkmnMoveDelete(HkmnMove **self);

void HkmnMoveReset(HkmnMove *self); // reset pp
HkmnEnvEnum HkmnMoveGetEnv(HkmnMove *self);

void HkmnMoveOp(HkmnMoveARGS); // always subtract pp by 1

#endif // HKMN_MOVE_H_
