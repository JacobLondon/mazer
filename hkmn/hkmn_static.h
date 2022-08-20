#ifndef HKMN_STATIC_H_
#define HKMN_STATIC_H_

#include "hkmn_move.h"
#include "hkmn_stat.h"
#include "hkmn_types.h"

#define DEFINE_MOVE_ENUM(MACRO) \
    MACRO(Tackle) \

typedef enum HkmnMoveOpEnum
{
#define XMOVES(Name) HkmnMoveOp##Name
    DEFINE_MOVE_ENUM(XMOVES)
#undef XMOVES
} HkmnMoveOpEnum;

HkmnMove *HkmnStaticMoveGet(HkmnMoveOpEnum move);

#endif // HKMN_STATIC_H_
