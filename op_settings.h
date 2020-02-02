// 设置操作
#ifndef _OP_SETTINGS_H
#define _OP_SETTINGS_H

// 声明函数
void update_settings(String item, String value);

// 修改设置的值
void update_settings(String item, String value) {
	if(item == "key_type") {
		if(value == "false") {
			s_key_type = false;
		}
		else if(value == "true") {
			s_key_type = true;
		}
	}
	else if(item == "bee_freq") {
		s_bee_freq = value.toInt();
	}
	else if(item == "split_time") {
		s_split_time = value.toInt();
	}
	else if(item == "auto_send_time") {
		s_auto_send_time = value.toInt();
	}
	else if(item == "shake_time") {
		s_shake_time = value.toInt();
	}
	else if(item == "play_u_time") {
		s_play_u_time = value.toInt();
	}
	else if(item == "u_time") {
		s_u_time = value.toInt();
	}
	else if(item == "auto_key_type") {
		if(value == "false") {
			s_auto_key_type = false;
		}
		else if(value == "true") {
			s_auto_key_type = true;
		}
	}
	else if(item == "auto_send") {
		if(value == "false") {
			s_auto_send = false;
		}
		else if(value == "true") {
			s_auto_send = true;
		}
	}
}




#endif