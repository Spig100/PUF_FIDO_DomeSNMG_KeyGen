#ifndef PUF_H
#define PUF_H

#include "pufs_basic.h"
#include "pufs_ka.h"

#define USBD_SERIAL_NUMBER\
    {'4', '1', '8', '2', '5', '5', '6', '6', '4', '2', '4', '8', '\0'}

int initDungle();
void deinitDungle();
void getDunglePrKey();
void getDunglePubKey();

#endif