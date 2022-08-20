#ifndef HKMN_STAT_H_
#define HKMN_STAT_H_

#include <stdio.h>
#include <stddef.h>

typedef struct HkmnStat HkmnStat;

HkmnStat *HkmnStatNew(float stat_value);
void HkmnStatDelete(HkmnStat **stat);
int HkmnStatGet(HkmnStat *stat);
int HkmnStatGetMax(HkmnStat *stat);
void HkmnStatDamage(HkmnStat *stat, float amount);
void HkmnStatHeal(HkmnStat *stat, float amount);
void HkmnStatReset(HkmnStat *stat);
void HkmnStatLevelup(HkmnStat *stat, float rate);

void HkmnStatDebuff(HkmnStat *stat);
void HkmnStatDebuffGreatly(HkmnStat *stat);
void HkmnStatBuff(HkmnStat *stat);
void HkmnStatBuffGreatly(HkmnStat *stat);

void HkmnSerialize(HkmnStat *stat, FILE *stream);
HkmnStat *HkmnDeserialize(char *buf, size_t size);

#endif // HKMN_H_

