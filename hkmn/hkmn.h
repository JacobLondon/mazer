#ifndef HKMN_H_
#define HKMN_H_

typedef enum HkmnLocationEnum
{
    HkmnLocationFLOOR       = 0x0,
    HkmnLocationSKY         = 0x1,
    HkmnLocationUNDERGROUND = 0x2,

    HkmnLocationFLOOR_SKY         = HkmnLocationFLOOR|HkmnLocationSKY,
    HkmnLocationFLOOR_UNDERGROUND = HkmnLocationFLOOR|HkmnLocationUNDERGROUND,
} HkmnLocationEnum;

typedef struct Hkmn Hkmn;

Hkmn *HkmnNew(const char *name, int level);
void HkmnDelete(Hkmn **self);

float HkmnGetHp(Hkmn *self);
float HkmnGetAccuracy(Hkmn *self);
float HkmnGetSpeed(Hkmn *self);
float HkmnGetAttack(Hkmn *self);
float HkmnGetDefense(Hkmn *self);
float HkmnGetSpAtk(Hkmn *self);
float HkmnGetSpDef(Hkmn *self);

void HkmnDamage(Hkmn *self, float amount); // always does AT LEAST 1 damage

/**
 * 2.0f if super effective
 * 1.0f if normally effective
 * 0.5f if not very effective
 * 
 * TODO: log the super/non effectiveness
 */
float HkmnTypeEffectiveness(Hkmn *self, HkmnTypeEnum type);

#endif // HKMN_H_
