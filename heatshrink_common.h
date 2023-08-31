#ifndef HEATSHRINK_H
#define HEATSHRINK_H

#include "heatshrink_config.h"

#define HEATSHRINK_AUTHOR "Scott Vokes <vokes.s@gmail.com>"
#define HEATSHRINK_URL "https://github.com/atomicobject/heatshrink"

/* Version 0.4.1 */
#define HEATSHRINK_VERSION_MAJOR 0
#define HEATSHRINK_VERSION_MINOR 4
#define HEATSHRINK_VERSION_PATCH 1

#define HEATSHRINK_MIN_WINDOW_BITS 4
#define HEATSHRINK_MAX_WINDOW_BITS 15

#define HEATSHRINK_MIN_LOOKAHEAD_BITS 3

#define HEATSHRINK_LITERAL_MARKER 0x01
#define HEATSHRINK_BACKREF_MARKER 0x00

#if defined(HEATSHRINK_NO_STD) && HEATSHRINK_NO_STD == 1

typedef unsigned int size_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef int int32_t;
typedef short int16_t;
typedef char int8_t;
typedef unsigned char bool;

void *memset(void *str, int c, unsigned int n);
void *memcpy(void *dest, const void *src, unsigned int n);
void *memmove(void *dest, const void *src, unsigned int n);

#define NULL 0

#endif

#endif
