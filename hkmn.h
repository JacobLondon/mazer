#ifndef HKMN_H_
#define HKMN_H_

typedef struct HkmnStat HkmnStat;

HkmnStat *HkmnStatNew(float stat_value);
void HkmnStatDelete(HkmnStat *stat);
float HkmnStatGet(HkmnStat *stat);
void HkmnStatDamage(HkmnStat *stat, float amount);
void HkmnStatHeal(HkmnStat *stat, float amount);
void HkmnStatReset(HkmnStat *stat);
void HkmnStatLevelup(HkmnStat *stat, float rate);

#endif // HKMN_H_

