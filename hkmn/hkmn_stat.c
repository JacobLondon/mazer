#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "hkmn_stat.h"
#include "util.h"

#define BUFF_DEBUFF_MAX 6

#define NUM_FIELDS 7
#define DEFINE_STATS(MACRO) \
    MACRO(float,  stat,     "%f ") \
    MACRO(float,  healing,  "%f ") \
    MACRO(float,  damage,   "%f ") \
    MACRO(int,    buff_ndx, "%d") \

struct HkmnStat {
#define XFIELDS(type, name, fmt) type name;
DEFINE_STATS(XFIELDS)
#undef XFIELDS
};

static float buff_lookup(int ndx)
{
    ndx += 6;
    assert(ndx >= 0);
    assert(ndx <= 12);

    static float _buff_lookup[(BUFF_DEBUFF_MAX*2)+1] = {
        [0] = 0.4f,
        [1] = 0.5f,
        [2] = 0.6f,
        [3] = 0.7f,
        [4] = 0.8f,
        [5] = 0.9f,
        [6] = 1.0f,
        [7] = 1.1f,
        [8] = 1.2f,
        [9] = 1.3f,
        [10] = 1.4f,
        [11] = 1.5f,
        [12] = 1.6f,
    };
    return _buff_lookup[ndx];
}

HkmnStat *HkmnStatNew(float stat_value)
{
    HkmnStat *stat = malloc(sizeof(*stat));
    assert(stat);
    memset(stat, 0, sizeof(*stat));

    stat->stat = stat_value;
    return stat;
}

void HkmnStatDelete(HkmnStat **ref)
{
    if (!ref) return;
    HkmnStat *self = *ref;
    memset(self, 0, sizeof(*self));
    free(self);
    *ref = NULL;
}

int HkmnStatGet(HkmnStat *stat)
{
    assert(stat);
    float result = (stat->stat * buff_lookup(stat->buff_ndx)) + stat->healing - stat->damage;
    CLAMP(result, stat->stat, 0);
    return (int)result;
}

int HkmnStatGetMax(HkmnStat *stat)
{
    assert(stat);
    return stat->stat;
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
    stat->buff_ndx = 0;
}

void HkmnStatLevelup(HkmnStat *stat, float rate)
{
    assert(stat);
    HkmnStatReset(stat);
    stat->stat *= rate;
}

static void buff(HkmnStat *stat, int amount)
{
    assert(stat);
    stat->buff_ndx += amount;
    CLAMP(stat->buff_ndx, BUFF_DEBUFF_MAX, -BUFF_DEBUFF_MAX);
}

void HkmnStatDebuff(HkmnStat *stat)
{
    assert(stat);
    debuff(stat, -1);
}

void HkmnStatDebuffGreatly(HkmnStat *stat)
{
    assert(stat);
    debuff(stat, -2);
}

void HkmnStatBuff(HkmnStat *stat)
{
    assert(stat);
    buff(stat, 1);
}

void HkmnStatBuffGreatly(HkmnStat *stat)
{
    assert(stat);
    buff(stat, 2);
}

void HkmnSerialize(HkmnStat *stat, FILE *stream)
{
    assert(stat);
    assert(stream);

#define XFORMAT(type, name, fmt) fmt
#define XNAMES(type, name, fmt) stat->name,

    fprintf(stream,
        DEFINE_STATS(XFORMAT) "%c",
        DEFINE_STATS(XNAMES) '\n');

#undef XFORMAT
#undef XNAMES
}

HkmnStat *HkmnDeserialize(char *buf, size_t size)
{
    char name[64];
    HkmnStat tmp;

    assert(buf);
    assert(size > 0);

#define XFORMAT(type, name, fmt) fmt
#define XNAMES(type, name, fmt) &tmp.name,

    int n;
    if (sscanf(buf, DEFINE_STATS(XFORMAT) "%n", DEFINE_STATS(XNAMES) &n) != (NUM_FIELDS+1))
    {
        return NULL;
    }

    HkmnStat *stat = HkmnStatNew(tmp.stat);
    stat->healing = tmp.healing;
    stat->damage = tmp.damage;
    return stat;
}
