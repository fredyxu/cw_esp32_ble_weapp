// 设置操作
#ifndef _OP_SETTINGS_H
#define _OP_SETTINGS_H

// 声明函数
void update_settings(String item, String value);

// 修改设置的值
void update_settings(String item, String value) {
	// Serial.println();
	// Serial.print(item);
	// Serial.print(" = ");
	// Serial.println(value);
	// 自动键手动建
	if(item == "key_type") {
		if(value == "false") {
			s_key_type = false;
		}
		else if(value == "true") {
			s_key_type = true;
		}
		set_settings("s_key_type", String(s_key_type));
	}
	// 蜂鸣器频率
	else if(item == "bee_freq") {
		s_bee_freq = value.toInt();
		set_settings("s_bee_freq", String(s_bee_freq));
	}
	// 字母之间的间隔时长
	else if(item == "split_time") {
		s_split_time = value.toInt();
		set_settings("s_split_time", String(s_split_time));
	}
	// 自动发送的间隔时长
	else if(item == "auto_send_time") {
		s_auto_send_time = value.toInt();
		set_settings("s_auto_send_time", String(s_auto_send_time));
	}
	// 防抖时长
	else if(item == "shake_time") {
		s_shake_time = value.toInt();
		set_settings("s_shake_time", String(s_shake_time));
	}
	// 播放单位时长
	else if(item == "play_u_time") {
		s_play_u_time = value.toInt();
		set_settings("s_play_u_time", String(s_play_u_time));
	}
	// 单位时长
	else if(item == "u_time") {
		s_u_time = value.toInt();
		set_settings("s_u_time", String(s_u_time));
	}
	// 自动按键是否左右交换
	else if(item == "auto_key_type") {
		if(value == "false") {
			s_auto_key_type = false;
		}
		else if(value == "true") {
			s_auto_key_type = true;
		}
		set_settings("s_auto_key_type", String(s_auto_key_type));
	}
	// 是否自动发送
	else if(item == "auto_send") {
		if(value == "false") {
			s_auto_send = false;
		}
		else if(value == "true") {
			s_auto_send = true;
		}
		set_settings("s_auto_send", String(s_auto_send));
	}
	// 是否使用触摸电键
	else if (item == "touch_key") {
		if(value == "false") {
			s_touch_key = false;
		}
		else if(value == "true") {
			s_touch_key = true;
		}
		set_settings("s_touch_key", String(s_touch_key));
	}
	// 触摸电键阈值
	else if(item == "touch_val") {
		s_touch_val = value.toInt();
		set_settings("s_touch_val", String(s_touch_val));
	}
	// 地狱模式
	else if(item == "exa_mode") {
		if(value == "false") {
			s_exa_mode = false;
		}
		else if(value == "true") {
			s_exa_mode = true;
		}
		set_settings("s_exa_mode", String(s_exa_mode));
	}
	// 点划时长比例
	else if(item == "di_da_scale") {
		s_di_da_scale = value.toFloat();
		set_settings("s_di_da_scale", String(s_di_da_scale));
	}
	// 容错率
	else if(item == "fault_rate") {
		s_fault_rate = value.toFloat();
		set_settings("s_fault_rate", String(s_fault_rate));
	}
}




#endif