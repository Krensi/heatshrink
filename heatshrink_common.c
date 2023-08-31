#include "heatshrink_common.h"

#if defined(HEATSHRINK_NO_STD) && HEATSHRINK_NO_STD == 1

void *my_memset(void *str, int c, unsigned int n)
{
    unsigned char *bytes = (unsigned char *)str;
    for (unsigned int i = 0; i < n; ++i)
    {
        bytes[i] = c;
    }

    return str;
}

void *my_memcpy(void *dest, const void *src, unsigned int n)
{
    unsigned char *bytes_dest = (unsigned char *)dest;
    unsigned char *bytes_src = (unsigned char *)src;
    for (unsigned int i = 0; i < n; ++i)
    {
        bytes_dest[i] = bytes_src[i];
    }

    return bytes_dest;
}

void *my_memmove(void *dest, const void *src, unsigned int n)
{
    unsigned char isCopyRequire = 0;  //flag bit
    char *pcSource =(char *)src;
    char *pcDstn =(char *)dest;
    // return if pcDstn and pcSource is NULL
    if ((pcSource == NULL) || (pcDstn == NULL))
    {
        return NULL;
    }
    // overlap buffer
    if((pcSource < pcDstn) && (pcDstn < pcSource + n))
    {
        for (pcDstn += n, pcSource += n; n--;)
        {
            *--pcDstn = *--pcSource;
        }
    }
    else
    {
        while(n--)
        {
            *pcDstn++ = *pcSource++;
        }
    }
    return dest;
}

#endif