#pragma once

#define NULL 0

void *my_memset(void *str, int c, unsigned long n);
void *my_memcpy(void *dest, const void *src, unsigned long n);
void *my_memmove(void *dest, const void *src, unsigned long n);