#ifndef UTIL_H_
#define UTIL_H_

#define OK_OR_RETURN(maybenull, rv) \
do { \
    if (!maybenull) return rv; \
} while (0)

#define MIN(a, b) ((a < b) ? (a) : (b))
#define MAX(a, b) ((a > b) ? (a) : (b))
#define CLAMP(a, max, min) \
do { \
    if      (a > max) a = max; \
    else if (a < min) a = min; \
} while (0)

#endif // UTIL_H_