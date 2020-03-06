// 手动电键
#ifndef _MANUAL_KEY_H
#define _MANUAL_KEY_H



// 函数声明
void check_manual_key();

void check_manual_key() {
	int diff_time = millis() - cs_time;
	// 抖动检查
	if(diff_time < s_shake_time) {
		return ;
	}

	bool touch_state = true;
	if(s_touch_key) {
		int touch_val_1 = touchRead(pin_touch_1);
		if(touch_val_1 == 0) {
			touch_val_1 = touchRead(pin_touch_1);
		}
		if(touch_val_1 < s_touch_val) {
			touch_state = false;
			Serial.println(touch_val_1);
		}
		// touch_state = touchRead(pin_touch_1) < s_touch_val? false: true;
	}

	// 读取引脚状态
	bool key_state = digitalRead(pin_key) && touch_state;
	
	// 如果是按下的，则初始化记录项目并蜂鸣器开始鸣叫
	if(!key_state && !flag_rcd) {
		flag_rcd = true;
		flag_space = false;
		cs_time = millis();
		bee(true);
	}

	// 如果被释放，切状态为记录状态，则检查键入电码，并停止蜂鸣器鸣叫
	else if(key_state && flag_rcd) {
		bee(false);
		// 如果大于单位时长，则视为输入的是划
		if(diff_time < s_u_time) {
			Serial.print(".");
			ble_send("code", ".");
		}
		// 否则视为是点
		else {
			Serial.print("-");
			ble_send("code", "-");
		}
		// 重新记录
		cs_time = millis();
		flag_rcd = false;
		flag_space = true;
	}
}

#endif