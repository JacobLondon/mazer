#include "hkmn_move.h"

#define CRIT_CHANCE .0625

struct HkmnMove
{
    int pp_used;
    const HkmnMoveDefinition *def;
};

static bool hits(HkmnMove *self)
{
    assert(self);
    if (rand_uniform() < self->def->accuracy) return true;
}

void HkmnMoveOp(HkmnMoveARGS)
{
    if (h_self->pp_used <= 0)
    {
        // out of pp or struggle? idk
        return;
    }

    // weather accuracy missing
    // if even affected by weather

    if (!hits(h_self))
    {
        return;
    }

    h_self->def->move(h_self, h_env, h_us, h_uscount, h_them, h_themcount);
}
