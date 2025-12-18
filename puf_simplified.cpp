#include "puf_simplified.hpp"

// Basics
int initDungle(){
    wchar_t serial_number[] = USBD_SERIAL_NUMBER;
    status = pufs_cmd_iface_init(serial_number);
    (status != SUCCESS) ? return 0 : return 1;
}

int deinitDungle(){
    wchar_t serial_number[] = USBD_SERIAL_NUMBER;
    status = pufs_cmd_iface_deinit(serial_number);
    (status != SUCCESS) ? return 0 : return 1;
}


