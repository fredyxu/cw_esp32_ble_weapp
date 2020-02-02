#ifndef _BLE_H
#define _BLE_H
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>


#define SERVICE_UUID "6880d7e7-93ba-4fdf-8940-31226ab93ac6"
#define CHARACTERISTIC_UUID "ccc5dfd0-6ce3-4f1a-9ab9-f7d9a88321ec"

BLECharacteristic *pCharacteristic;

// 初始化蓝牙
void ble_init();
// 发送信息
void ble_send(String msg);
// 处理收到的信息
void ble_op_msg(String msg);
// 分割字符串
void str_split(String s,String p);

void ble_send(String msg_type, String msg)
{
	if(msg_type == "code") {
		msg = "inp:" + msg;
	}
	else if(msg_type == "cmd") {
		msg = "cmd:" + msg;
	}
	pCharacteristic->setValue((char *)msg.c_str());
	pCharacteristic->notify();
}

class callback: public BLECharacteristicCallbacks {
	void onWrite(BLECharacteristic *pCharacteristic) {
		std::string value = pCharacteristic->getValue();
		if(value.length() > 0) {
			ble_op_msg(value.c_str());
		}
	}
};


void ble_op_msg(String msg) {
	// 分割信息
	String info[] = {"", "", ""};
	int p = 0;
	for(int i = 0; i < msg.length(); i++) {
		if(msg[i] == ':') {
			p++;
			continue;
		}
		info[p] += msg[i];
	}

	// 设置参数
	if(info[0] == "set") {
		update_settings(info[1], info[2]);
	}
	// 播放电码
	if(info[0] == "ply") {
		play_code(info[1]);
	}
}

void ble_init() {
	BLEDevice::init("ZClub CW");
	BLEServer *pServer = BLEDevice::createServer();
	BLEService *pService = pServer->createService(SERVICE_UUID);
	pCharacteristic = pService->createCharacteristic(
		CHARACTERISTIC_UUID,
		BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY
		// | BLECharacteristic::PROPERTY_INDICATE
	);
	pCharacteristic->setCallbacks(new callback());
	pService->start();
	BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
	pAdvertising->addServiceUUID(SERVICE_UUID);
	pAdvertising->setScanResponse(true);
	pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
	pAdvertising->setMinPreferred(0x12);
	BLEDevice::startAdvertising();
	Serial.println("蓝牙初始化完成");
}



#endif