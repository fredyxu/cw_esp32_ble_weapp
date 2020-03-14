// 设置操作
#ifndef _OP_SETTINGS_H
#define _OP_SETTINGS_H

// 声明函数
void update_settings(String item, String value);

// 修改设置的值
void update_settings(String item, String value) {
	// 自动键手动建
	if(item == "key_type") {
		if(value == "false") {
			s_key_type = false;
		}
		else if(value == "true") {
			s_key_type = true;
		}
	}
	// 蜂鸣器频率
	else if(item == "bee_freq") {
		s_bee_freq = value.toInt();
	}
	// 字母之间的间隔时长
	else if(item == "split_time") {
		s_split_time = value.toInt();
	}
	// 自动发送的间隔时长
	else if(item == "auto_send_time") {
		s_auto_send_time = value.toInt();
	}
	// 防抖时长
	else if(item == "shake_time") {
		s_shake_time = value.toInt();
	}
	// 播放单位时长
	else if(item == "play_u_time") {
		s_play_u_time = value.toInt();
	}
	// 单位时长
	else if(item == "u_time") {
		s_u_time = value.toInt();
	}
	// 自动按键是否左右交换
	else if(item == "auto_key_type") {
		if(value == "false") {
			s_auto_key_type = false;
		}
		else if(value == "true") {
			s_auto_key_type = true;
		}
	}
	// 是否自动发送
	else if(item == "auto_send") {
		if(value == "false") {
			s_auto_send = false;
		}
		else if(value == "true") {
			s_auto_send = true;
		}
	}
	// 是否使用触摸电键
	else if (item == "touch_key") {
		if(value == "false") {
			s_touch_key = false;
		}
		else if(value == "true") {
			s_touch_key = true;
		}
	}
	// 触摸电键阈值
	else if(item == "touch_val") {
		s_touch_val = value.toInt();
	}
}




#endif