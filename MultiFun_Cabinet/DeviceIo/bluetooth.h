#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#ifdef __cplusplus
extern "C" {
#endif
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<termios.h>
#include<errno.h>
#include<string.h>
#include <sys/select.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <linux/prctl.h>
#include <sys/signalfd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <stdio.h>
#include "DeviceIo/RkBtBase.h"
#include "DeviceIo/RkBtSource.h"
#include "RkBle.h"

#define BLE_UUID_SERVICE	"0000180A-0000-1000-8000-00805F9B34FB"
#define BLE_UUID_WIFI_CHAR	"00009999-0000-1000-8000-00805F9B34FB"
#define BLE_UUID_PROXIMITY	"7B931104-1810-4CBC-94DA-875C8067F845"
#define BLE_UUID_SEND		"dfd4416e-1810-47f7-8248-eb8be3dc47f9"
#define BLE_UUID_RECV		"9884d812-1810-4a24-94d3-b2c11a851fac"
#define SERVICE_UUID		"00001910-0000-1000-8000-00805f9b34fb"

void c_initBt();
void c_openBt();

void bt_test_ble_recv_data_callback(const char *uuid, char *data, int len);

void bt_test_ble_request_data_callback(const char *uuid);

void bt_test_state_cb(RK_BT_STATE state);

void bt_test_bond_state_cb(const char *bd_addr, const char *name, RK_BT_BOND_STATE state);

#ifdef __cplusplus
}
#endif
#endif
