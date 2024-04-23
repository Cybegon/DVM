#include "dvmutils.h"

dsize dvm_strcmp(const char* s1, const char* s2)
{
    while(*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }

    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

dsize dvm_strncmp(const char* s1, const char* s2, dsize n)
{
    while(n && *s1 && (*s1 == *s2)) {
        s1++;
        s2++;
        --n;
    }

    return (n != 0) ? *(const unsigned char*)s1 - *(const unsigned char*)s2 : 0;
}

dsize dvm_strlen(const char* str)
{
    const char* strTmp = str;

    for (; *strTmp; ++strTmp);

    return (strTmp - str);
}
