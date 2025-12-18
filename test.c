#include "pufs_simplified.hpp"
#include "util.hpp"

#include "pufs_basic.h"
#include "pufs_ka.h"
#include "pufs_rt.h"
#include "pufs_kdf.h"
#include "pufs_pkc.h"

#include <stdio.h>
#include <stdlib.h>

int main(void){
    if (initDungle() == 1) {
        deinitDungle();
        printf("Did't init sucessfully\n");
        return 1;
    }
    pufs_ec_point_st pubKey = getPubKey();

    printf("Your key: \n");
    printUint8InArray(pubKey.x, 72);
    printf("\n");
    printUint8InArray(pubKey.y, 72);
    printf("\n");

    deinitDungle();

    return 0;
}