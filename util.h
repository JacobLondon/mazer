#ifndef UTIL_H_
#define UTIL_H_

#define OK_OR_RETURN(maybenull, rv) \
do { \
    if (!maybenull) return rv; \
} while (0)

#endif // UTIL_H_