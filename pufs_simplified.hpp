#ifndef PUF_H
#define PUF_H
#include "pufs_basic.h"
#include "pufs_ka.h"
#include "pufs_rt.h"
#include "pufs_kdf.h"
#include "pufs_pkc.h"

#include <stdlib.h>
#include <stdio.h>

#define USBD_SERIAL_NUMBER                                                  \
    {                                                                       \
        '4', '1', '8', '2', '5', '5', '6', '6', '4', '2', '4', '8', '\0'    \
    }

const char* errorTypeListenum[] = {
    "SUCCESS",                /**< Success. */
    "E_ALIGN",                /**< Address alignment mismatch. */
    "E_OVERFLOW",             /**< Space overflow. */
    "E_UNDERFLOW",            /**< Size too small. */
    "E_INVALID",              /**< Invalid argument. */
    "E_BUSY",                 /**< Resource is occupied. */
    "E_UNAVAIL",              /**< Resource is unavailable. */
    "E_FIRMWARE",             /**< Firmware error. */
    "E_VERFAIL",              /**< Invalid public key or digital signature. */
    "E_ECMPROG",              /**< Invalid ECC microprogram. */
    "E_DENY",                 /**< Access denied. */
    "E_UNSUPPORT",            /**< Not support. */
    "E_INFINITY",             /**< Point at infinity. */
    "E_ERROR",                /**< Unspecific error. */
    /* Interface Error */
    "E_IFACE_INIT_FAIL",      /**< Interface initial fail. */
    "E_IFACE_NOT_INIT",       /**< Interface has not initial */
    "E_IFACE_BAD_PARAM",      /**< Invalid parameters for interface hal api */
    "E_IFACE_COMM_FAIL",      /**< Interface communication fail */
    "E_IFACE_TX_FAIL",        /**< Interface transmit fail */
    "E_IFACE_RX_FAIL",        /**< Interface receive fail */
    /* Command Error */
    "E_CMD_BAD_PARAM",        /**< Invalid parameters for pufs cmd api */
    "E_CMD_BAD_RETURN_PARAM", /**< Invalid return parameters for pufs cmd api */

};

int initDungle(void);
int deinitDungle(void);
pufs_ec_point_st getPubKey(void);
void printPUFError(pufs_status_t status, char* errorMes);

// Basics
int initDungle(void){
    wchar_t serial_number[] = USBD_SERIAL_NUMBER;
    pufs_status_t status = pufs_cmd_iface_init(serial_number);
    if (status != SUCCESS){
        return 0;
    }
    return 1;
}

int deinitDungle(void){
    pufs_status_t status = pufs_cmd_iface_deinit();
    if (status != SUCCESS){
        return 0;
    }
    return 1;
}

void printPUFError(pufs_status_t status, char* errorMes){
    printf("%s", errorMes);
    printf("Error type: %s\n", errorTypeListenum[status]);
    deinitDungle();
    exit(1);
    return;
}

// Gaining Public Key from PUF dungle
pufs_ec_point_st getPubKey(void){

    pufs_status_t status;
    
    status = pufs_ecp_set_curve_byname(NISTP256);
	
    if (status != SUCCESS)
		printPUFError(status, "Set curve failed.\n");

    pufs_key_type_t ECPrKeyType = PRKEY;
    pufs_ka_slot_t ECPrKeySlot = PRK_0;

    pufs_ec_point_st pubKey;
    status = pufs_ecp_gen_puk(&pubKey, ECPrKeyType, ECPrKeySlot);

    if (status != SUCCESS){
        printPUFError(status, "ECPubKey hasn't been successfully gained.\n");
    }

    return pubKey;
}


#endif