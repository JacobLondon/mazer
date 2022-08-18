#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "hkmn.h"
#include "util.h"

#define HKMN_FORMAT "%63s %f %f %f"

struct HkmnStat {
    char *name;
    float stat;
    float healing;
    float damage;
};

HkmnStat *HkmnStatNew(const char *name, float stat_value)
{
    HkmnStat *stat = malloc(sizeof(*stat));
    assert(stat);
    memset(stat, 0, sizeof(*stat));
    stat->name = strdup(name);
    assert(stat->name);

    stat->stat = stat_value;
    return stat;
}

void HkmnStatDelete(HkmnStat *stat)
{
    if (!stat) return;
    if (stat->name)
    {
        free(stat->name);
    }
    memset(stat, 0, sizeof(*stat));
    free(stat);
}

float HkmnStatGet(HkmnStat *stat)
{
    assert(stat);
    float result = stat->stat + stat->healing - stat->damage;
    CLAMP(result, stat->stat, 0);
    return result;
}

void HkmnStatDamage(HkmnStat *stat, float amount)
{
    assert(stat);
    stat->damage += amount;
}

void HkmnStatHeal(HkmnStat *stat, float amount)
{
    stat->healing += amount;
}

void HkmnStatReset(HkmnStat *stat)
{
    assert(stat);
    stat->healing = 0;
    stat->damage = 0;
}

void HkmnStatLevelup(HkmnStat *stat, float rate)
{
    assert(stat);
    HkmnStatReset(stat);
    stat->stat *= rate;
}

void HkmnSerialize(HkmnStat *stat, FILE *stream)
{
    assert(stat);
    assert(stream);

    fprintf(stream, HKMN_FORMAT, stat->name, stat->stat, stat->healing, stat->damage);
}

HkmnStat *HkmnDeserialize(char *buf, size_t size)
{
    char name[64];
    HkmnStat tmp;
    tmp.name = name;

    assert(buf);
    assert(size > 0);

    if (sscanf(buf, HKMN_FORMAT, tmp.name, &tmp.stat, &tmp.healing, &tmp.damage) != 4) {
        return NULL;
    }

    HkmnStat *stat = HkmnStatNew(name, tmp.stat);
    stat->healing = tmp.healing;
    stat->damage = tmp.damage;
    return stat;
}
