#ifndef _AUTO_KEY_H
#define _AUTO_KEY_H

void check_auto_key();

void check_auto_key() {
	// 抖动检查
	int diff_time = millis() - cs_time;
	
	if(diff_time < s_shake_time) {
		return ;
	}
	bool touch_state_1 = true;
	bool touch_state_2 = true;
	if(s_touch_key) {
		// 读取触摸引脚时，偶尔会出现读未触摸读取值仍然为0的情况（原因待查）。为排除此情况故在读取值为0时进行第二次读取，确保读取到实际触摸所引发的数值。
		int touch_val_1 = touchRead(pin_touch_1);
		if(touch_val_1 == 0) {
			touch_val_1 = touchRead(pin_touch_1);
		}
		int touch_val_2 = touchRead(pin_touch_2);
		if(touch_val_2 == 0) {
			touch_val_2 = touchRead(pin_touch_2);
		}
		
		if(touch_val_1 < s_touch_val) {
			touch_state_1 = false;
		}
		if(touch_val_2 < s_touch_val) {
			touch_state_2 = false;
		}
	}

	bool di_state = true;
	bool da_state = true;
	if(s_auto_key_type) {
		di_state = digitalRead(pin_key_di) && touch_state_1;
		da_state = digitalRead(pin_key_da) && touch_state_2;
	}
	else {
		di_state = digitalRead(pin_key_da) && touch_state_2;
		da_state = digitalRead(pin_key_di) && touch_state_1;
	}
	
	// 电码间隔
	int sp_time = s_u_time / 2;
	if(!di_state) {
		bee(true);
		Serial.print(".");
		ble_send("code", ".");
		delay(s_u_time / 2);
		bee(false);
		delay(sp_time);
		flag_space = true;
		cs_time = millis();
	}
	
	if(!da_state) {
		bee(true);
		Serial.print("-");
		ble_send("code", "-");
		delay(s_u_time * 1.5);
		bee(false);
		delay(sp_time);
		flag_space = true;
		cs_time = millis();
	}
}

#endif