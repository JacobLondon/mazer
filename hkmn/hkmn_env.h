#ifndef HKMN_ENV_H_
#define HKMN_ENV_H_

#include <stdbool.h>

typedef enum HkmnEnvEnum
{
    HkmnEnvCLEAR   = 0x1,
    HkmnEnvRAINING = 0x2,
    HkmnEnvSUNNY   = 0x4,

    HkmnEnvCLEAR_OR_RAINING = HkmnEnvCLEAR|HkmnEnvRAINING,
    HkmnEnvCLEAR_OR_SUNNY   = HkmnEnvCLEAR|HkmnEnvSUNNY,
    HkmnEnvANY = 0xFF,
} HkmnEnvEnum;

typedef struct HkmnEnvironment HkmnEnvironment;

HkmnEnvEnum HkmnEnvironmentGet(HkmnEnvironment *env);
bool HkmnEnvironmentCompatible(HkmnEnvironment *env, HkmnEnvEnum query);

#endif // HKMN_ENV_H_
