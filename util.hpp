#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdint.h>

void printUint8InArray(const uint8_t* buf, uint32_t len);

void printUint8InArray(const uint8_t* buf, uint32_t len)
{
	printf("{");
	for (uint32_t i = 0; i < len; ++i) {
		printf("0x%02X%c", buf[i], i == len - 1 ? '}' : ',');
	}
    return;
}

#endif