#include "pin.h"
#include "var_settings.h"
#include "var_morse.h"
#include "op_bee.h"
#include "op_settings.h"
#include "op_code.h"
// 在op_code.h中包含ble.h
// #include "ble.h"
#include "time_tools.h"
#include "auto_key.h"
#include "manual_key.h"
#include "time_tools.h"


void setup() {
	// 初始化引脚
	pinMode(pin_bee, OUTPUT);
	pinMode(pin_key, INPUT_PULLUP);
	pinMode(pin_key_di, INPUT_PULLUP);
	pinMode(pin_key_da, INPUT_PULLUP);
	// 触摸引脚
	pinMode(pin_touch_1, INPUT);
	pinMode(pin_touch_2, INPUT);

	// 初始化串口
	Serial.begin(115200);
	Serial.println();
	Serial.println("串口初始化完成");

	// 初始化蜂鸣器
	ledcSetup(0, s_bee_freq, 10);
	ledcAttachPin(pin_bee, 0);

	ble_init();
	
	Serial.println("初始化完成");

}

void loop() {
	// 检查空格
	check_space();
	// 检查自动发送
	check_send();
	// 手动建
	if (s_key_type)
	{
		check_manual_key();
	}
	// 自动键
	else if(!s_key_type) {
		check_auto_key();
	}
}