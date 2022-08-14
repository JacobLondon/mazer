#include <assert.h>
#include <stdlib.h>
#include "hkmn.h"

struct HkmnStat {
    float stat;
    float healing;
    float damage;
};

HkmnStat *HkmnStatNew(float stat_value)
{
    HkmnStat *stat = malloc(sizeof(*stat));
    assert(stat);
    memset(stat, 0, sizeof(*stat));

    stat->stat = stat_value;
    return stat;
}

void HkmnStatDelete(HkmnStat *stat)
{
    if (!stat) return;
    memset(stat, 0, sizeof(*stat));
    free(stat);
}

float HkmnStatGet(HkmnStat *stat)
{
    assert(stat);
    return stat->stat + stat->modifier;
}

void HkmnStatDamage(HkmnStat *stat, float amount)
{
    assert(stat);
}

void HkmnStatHeal(HkmnStat *stat, float amount)
{
    
}

void HkmnStatReset(HkmnStat *stat)
{
    assert(stat);
}

void HkmnStatLevelup(HkmnStat *stat, float rate)
{
    assert(stat);
}

