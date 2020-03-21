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


	bool key_state_di = digitalRead(pin_key_di);
	bool key_state_da = digitalRead(pin_key_da);

	
	if(s_auto_key_type) {
		di_state = key_state_di && touch_state_1;
		da_state = key_state_da && touch_state_2;
	}
	else {
		di_state = key_state_da && touch_state_2;
		da_state = key_state_di && touch_state_1;
	}

	// 测试
	if(!di_state || !da_state) {
		Serial.println();
		Serial.println("===============");
		Serial.print("DI_STATE: ");
		Serial.println(di_state);
		Serial.print("key_state_di: ");
		Serial.println(key_state_di);
		Serial.print("touch_state_1: ");
		Serial.println(touch_state_1);

		Serial.println("---------");

		Serial.print("DA_STATE: ");
		Serial.println(da_state);
		Serial.print("key_state_da: ");
		Serial.println(key_state_da);
		Serial.print("touch_state_2: ");
		Serial.println(touch_state_2);
		Serial.println("===============");

		


		if(!key_state_di) {
			Serial.println("pin_di");
		}
		if(!key_state_da) {
			Serial.println("pin_da");
			Serial.println(digitalRead(pin_key_da));
		}
		if(!touch_state_1) {
			Serial.println("touch_1");
		}
		if(!touch_state_2) {
			Serial.println("touch_2");
		}

		Serial.println();
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