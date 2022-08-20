
#include "hkmn_move.h"
#include "hkmn_stat.h"
#include "hkmn_types.h"
#include "hkmn.h"

struct Hkmn {
    char *name;
    union {
        struct {
            HkmnStat *hp;
            HkmnStat *speed;
            HkmnStat *accuracy;

            HkmnStat *attack;
            HkmnStat *defense;
            HkmnStat *spatk;
            HkmnStat *spdef;
        };
        HkmnStat *stats[7];
    };
    HkmnLocationEnum location;
    HkmnTypeEnum type;
    HkmnMove *moves[4];
};


