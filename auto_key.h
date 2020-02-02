#ifndef _AUTO_KEY_H
#define _AUTO_KEY_H

void check_auto_key();

void check_auto_key() {
	// 抖动检查
	int diff_time = millis() - cs_time;
	
	if(diff_time < s_shake_time) {
		return ;
	}

	int di_state = digitalRead(pin_key_di);
	int da_state = digitalRead(pin_key_da);

	// 电码间隔
	int sp_time = s_u_time / 2;
	if(di_state == 0) {
		bee(true);
		Serial.print(".");
		ble_send("code", ".");
		delay(s_u_time / 2);
		bee(false);
		delay(sp_time);
		flag_space = true;
		cs_time = millis();
	}
	
	if(da_state == 0) {
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