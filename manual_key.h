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
		}
		// touch_state = touchRead(pin_touch_1) < s_touch_val? false: true;
	}
	bool pin_state = digitalRead(pin_key);
	// 读取引脚状态
	bool key_state = pin_state && touch_state;

	
	// 如果是按下的，则初始化记录项目并蜂鸣器开始鸣叫
	if(!key_state && !flag_rcd) {
		flag_rcd = true;
		flag_space = false;
		cs_time = millis();
		bee(true);
	}

	// 如果被释放，切状态为记录状态，则检查键入电码，并停止蜂鸣器鸣叫
	else if(key_state && flag_rcd) {
		Serial.println(s_exa_mode);
		bee(false);
		// 非严格模式
		if(!s_exa_mode) {
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
		}
		// 地狱模式
		else {
			int di_min = (float)s_u_time * (float)(1.0 - s_fault_rate);
			int di_max = (float)s_u_time * (float)(1.0 + s_fault_rate);
			int da_min = (float)s_u_time * (float)(1.0 - s_fault_rate) * (float)s_di_da_scale; 
			int da_max = (float)s_u_time * (float)(1.0 + s_fault_rate) * (float)s_di_da_scale;
			
			// 以下为测试，
			// Serial.println();
			// Serial.print("di_min: ");
			// Serial.print(di_min); 
			// Serial.print("  di_max: ");
			// Serial.print(di_max);
			// Serial.print("    |    da_min: ");
			// Serial.print(da_min);
			// Serial.print(" da_max: ");
			// Serial.print(da_max);
			// Serial.print("   |   input_time: ");
			// Serial.println(diff_time);

			if(diff_time >= di_min && diff_time <= di_max) {
				Serial.print(".");
				ble_send("code", ".");
			}
			else if(diff_time >= da_min && diff_time <= da_max) {
				Serial.print("-");
				ble_send("code", "-");
			}
			else {
				Serial.print("*");
				ble_send("code", "*");
			}
		}
		// 重新记录
		cs_time = millis();
		flag_rcd = false;
		flag_space = true;
	}
}

#endif