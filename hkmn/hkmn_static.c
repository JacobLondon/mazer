#include "hkmn_static.h"

/**
 * All moves
 * All hkmn templates
 * All hkmn move acquisitions at each level
 */

#define MOVE(Name, Location, Env, Type, Pp, Power, Accuracy, Body) \
static void Name##Func(HkmnMoveARGS); \
static void Name##Func(HkmnMoveARGS) \
{ \
    HkmnMoveARGS_OK(); \
    Body \
} \
static HkmnMoveDefinition Name = { \
    .name = #Name, \
    .location = Location, \
    .env = Env, \
    .type = Type, \
    .move = Name##Func, \
    .pp = Pp, \
    .power = Power, \
    .accuracy = Accuracy, \
}

MOVE(Tackle, HkmnLocationFLOOR, HkmnEnvANY, HkmnTypeNORMAL, 30, 40.0, 1.00, {
    const float attack = HkmnGetAttack(h_us[0]);
    const float defense = HkmnGetDefense(h_them[0]);
    const float effectiveness = HkmnTypeEffectiveness(h_them[0], Tackle.type);
    float damage = Tackle.power * attack / defense * effectiveness;
    HkmnDamage(h_them[0], damage);
});

static HkmnMove *moves[] = {
#define XMOVES(Name) &Name,
    DEFINE_MOVE_ENUM(XMOVES)
#undef XMOVES
};

HkmnMove *HkmnStaticMoveGet(HkmnMoveOpEnum move)
{
    return moves[move];
}
