#include "bluetooth.h"

static RkBtContent bt_content;

void c_openBt()
{
    rk_bt_source_open();
}
void c_initBt()
{
    printf("%s: BT BLUETOOTH INIT\n", __func__);

    int len, ble_name_len, remain_len;

    memset(&bt_content, 0, sizeof(RkBtContent));
    bt_content.bt_name = "ROCKCHIP_AUDIO";
    //bt_content.bt_addr = "11:22:33:44:55:66";

    bt_content.ble_content.ble_name = "ROCKCHIP_AUDIO_BLE";
    bt_content.ble_content.server_uuid.uuid = SERVICE_UUID;
    bt_content.ble_content.server_uuid.len = UUID_128;
    bt_content.ble_content.chr_uuid[0].uuid = BLE_UUID_SEND;
    bt_content.ble_content.chr_uuid[0].len = UUID_128;
    bt_content.ble_content.chr_uuid[1].uuid = BLE_UUID_RECV;
    bt_content.ble_content.chr_uuid[1].len = UUID_128;
    bt_content.ble_content.chr_cnt = 2;

    bt_content.ble_content.advDataType = BLE_ADVDATA_TYPE_USER;

    //标识设备 LE 物理连接的功能
    bt_content.ble_content.advData[1] = 0x02;
    bt_content.ble_content.advData[2] = 0x01;
    bt_content.ble_content.advData[3] = 0x02;

    //service uuid(SERVICE_UUID)
    bt_content.ble_content.advData[4] = 0x03;
    bt_content.ble_content.advData[5] = 0x03;
    bt_content.ble_content.advData[6] = 0x10;
    bt_content.ble_content.advData[7] = 0x19;

    //ble name
    printf("ble_name_len: %s(%d)\n", bt_content.ble_content.ble_name, strlen(bt_content.ble_content.ble_name));
    ble_name_len = strlen(bt_content.ble_content.ble_name);
    remain_len = 31 - (bt_content.ble_content.advData[1] + 1)
                    - (bt_content.ble_content.advData[4] + 1);
    len = ble_name_len > remain_len ? remain_len : ble_name_len;
    bt_content.ble_content.advData[8] = len + 1;
    bt_content.ble_content.advData[9] = 0x09;
    memcpy(&bt_content.ble_content.advData[10], bt_content.ble_content.ble_name, len);

    bt_content.ble_content.advData[0] = bt_content.ble_content.advData[1] + 1
                                        + bt_content.ble_content.advData[4] + 1
                                        + bt_content.ble_content.advData[8] + 1;
    bt_content.ble_content.advDataLen = bt_content.ble_content.advData[0] + 1;

    //==========================rsp======================
    bt_content.ble_content.respData[1] = 0x16;  //长度
    bt_content.ble_content.respData[2] = 0xFF;  //字段类型

    /*厂商编码*/
    bt_content.ble_content.respData[3] = 0x46;
    bt_content.ble_content.respData[4] = 0x00;

    bt_content.ble_content.respData[5] = 0x02;  //项目代号长度

    /*项目代号*/
    bt_content.ble_content.respData[6] = 0x1c;
    bt_content.ble_content.respData[7] = 0x02;

    bt_content.ble_content.respData[8] = 0x04;  //版本号长度
    bt_content.ble_content.respData[9] = 'T';   //版本号类型
    /*版本号*/
    bt_content.ble_content.respData[10] = 0x01;
    bt_content.ble_content.respData[11] = 0x00;
    bt_content.ble_content.respData[12] = 0x00;

    bt_content.ble_content.respData[13] = 0x08;	// SN长度
    /*SN号*/
    bt_content.ble_content.respData[14] = 0x54;
    bt_content.ble_content.respData[15] = 0x00;
    bt_content.ble_content.respData[16] = 0x00;
    bt_content.ble_content.respData[17] = 0x00;
    bt_content.ble_content.respData[18] = 0x00;
    bt_content.ble_content.respData[19] = 0x00;
    bt_content.ble_content.respData[20] = 0x00;
    bt_content.ble_content.respData[21] = 0x36;

    bt_content.ble_content.respData[22] = 0x01;	//绑定信息长度
    bt_content.ble_content.respData[23] = 0x00;	//绑定信息

    bt_content.ble_content.respData[0] = bt_content.ble_content.respData[1] + 1;  //长度
    bt_content.ble_content.respDataLen = bt_content.ble_content.respData[0] + 1;

    bt_content.ble_content.cb_ble_recv_fun = bt_test_ble_recv_data_callback;
    bt_content.ble_content.cb_ble_request_data = bt_test_ble_request_data_callback;
    rk_bt_register_state_callback(bt_test_state_cb);
    rk_bt_register_bond_callback(bt_test_bond_state_cb);
    rk_bt_init(&bt_content);

    return NULL;
}

void bt_test_ble_recv_data_callback(const char *uuid, char *data, int len)
{
    char data_t[512];
    char reply_buf[512] = {"My name is rockchip"};

    printf("=== %s uuid: %s===\n", __func__, uuid);
    memcpy(data_t, data, len);
    for (int i = 0 ; i < len; i++) {
        printf("%02x ", data_t[i]);
    }
    printf("\n");

    if (strstr(data_t, "Hello RockChip") || strstr(data_t, "HelloRockChip") ||
        strstr(data_t, "HELLO ROCKCHIP") || strstr(data_t, "HELLOROCKCHIP") ||
        strstr(data_t, "hello rockchip") || strstr(data_t, "hellorockchip")) {
        printf("=== %s Reply:%s ===\n", __func__, reply_buf);
        rk_ble_write(uuid, reply_buf, 17);
    }
}

void bt_test_ble_request_data_callback(const char *uuid)
{
    printf("=== %s uuid: %s===\n", __func__, uuid);
    //rk_ble_write(uuid, "Hello Rockchip", strlen("Hello Rockchip"));

//	send_data(uuid);
}


void bt_test_state_cb(RK_BT_STATE state)
{
    switch(state) {
        case RK_BT_STATE_TURNING_ON:
            printf("++++++++++ RK_BT_STATE_TURNING_ON ++++++++++\n");
            break;
        case RK_BT_STATE_ON:
            printf("++++++++++ RK_BT_STATE_ON ++++++++++\n");
//			gonff = true;
            break;
        case RK_BT_STATE_TURNING_OFF:
            printf("++++++++++ RK_BT_STATE_TURNING_OFF ++++++++++\n");
            break;
        case RK_BT_STATE_OFF:
            printf("++++++++++ RK_BT_STATE_OFF ++++++++++\n");
//			gonff = false;
            break;
    }
}

void bt_test_bond_state_cb(const char *bd_addr, const char *name, RK_BT_BOND_STATE state)
{
    switch(state) {
        case RK_BT_BOND_STATE_NONE:
            printf("++++++++++ BT BOND NONE: %s, %s ++++++++++\n", name, bd_addr);
            break;
        case RK_BT_BOND_STATE_BONDING:
            printf("++++++++++ BT BOND BONDING: %s, %s ++++++++++\n", name, bd_addr);
            break;
        case RK_BT_BOND_STATE_BONDED:
            printf("++++++++++ BT BONDED: %s, %s ++++++++++\n", name, bd_addr);
            break;
    }
}
