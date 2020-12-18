#ifndef _OP_EEPROM_H
#define _OP_EEPROM_H

#include <EEPROM.h>

// 初始化EEPROM
void init_eeprom();
void set_settings(String item, String value);
void set_value(int i, String value);
String get_settings(String item);
String get_value(int i);
bool check_first_run();

String per_code = "BG7YXY";

// 设置项目个数
#define settings_qty 14
// 每个项目所占用的字节
#define settings_char_qty 5

// s_key_type
// s_bee_freq
// s_split_time
// s_auto_send_time
// s_shake_time
// s_play_u_time
// s_u_time
// s_auto_key_type
// s_auto_send
// s_touch_key
// s_touch_val

String settings_item[] = {
	"s_key_type", 
	"s_bee_freq", 
	"s_split_time", 
	"s_auto_send_time", 
	"s_shake_time", 
	"s_play_u_time", 
	"s_u_time", 
	"s_auto_key_type", 
	"s_auto_send", 
	"s_touch_key", 
	"s_touch_val",
	"s_exa_mode",
	"s_di_da_scale",
	"s_fault_rate",
};

// 初始化
void init_eeprom() {
	EEPROM.begin((settings_qty * settings_char_qty) + per_code.length());
}


// 存储
void set_settings(String item, String value)  {
	if (item != "all") {
		for(int i =0; i < settings_qty; i ++) {
			if(settings_item[i] == item) {
				set_value(i, value);
				return ;
			}
		}
	}
}



// 设置值
void set_value(int i, String value) {
	for(int j = 0; j < settings_char_qty; j++) {
		char c = '0';
		if(j >= settings_char_qty - value.length()) {
			c = value[j - settings_char_qty + value.length()];
		}
		EEPROM.write(i * settings_char_qty + j, c);
	}
	EEPROM.commit();
}

String get_settings(String item) {
	if(item != "all") {
		for(int i =0; i < settings_qty; i ++) {
			if(settings_item[i] == item) {
				return get_value(i);
			}
		}
	}
}


String get_value(int i) {
	String value = "";
	for (int j = 0; j < settings_char_qty; j ++) {
		char c = EEPROM.read(i * settings_char_qty + j);
		value += c;
	}
	return value;
}

// 检查是否是首次运行
bool check_first_run() {
	String code = "";
	for(int i = 0; i < per_code.length(); i ++) {
		char c = EEPROM.read(settings_qty * settings_char_qty + i);
		code += c;
	}
	if(code == per_code) {
		return false;
	}
	else {
		return true;
	}
}

void set_per_code() {
	for(int i = 0; i < per_code.length(); i ++) {
		EEPROM.write(settings_qty * settings_char_qty + i, per_code[i]);
	}
	EEPROM.commit();
}

void set_all_settings() {
	// s_key_type
	set_settings("s_key_type", String(s_key_type));
	// bee_freq
	set_settings("s_bee_freq", String(s_bee_freq));
	// auto_send_time
	set_settings("s_auto_send_time", String(s_auto_send_time));
	// shake_time
	set_settings("s_shake_time", String(s_shake_time));
	// play_u_time
	set_settings("s_play_u_time", String(s_play_u_time));
	// u_time
	set_settings("s_u_time", String(s_u_time));
	// auto_key_type
	set_settings("s_auto_key_type", String(s_auto_key_type));
	// auto_send
	set_settings("s_auto_send", String(s_auto_send));
	// touch_key
	set_settings("s_touch_key", String(s_touch_key));
	// touch_val
	set_settings("s_touch_val", String(s_touch_val));
	// s_exa_mode
	set_settings("s_exa_mode", String(s_exa_mode));
	// s_di_da_scale
	set_settings("s_di_da_scale", String(s_di_da_scale));
	// s_fault_rate
	set_settings("s_fault_rate", String(s_fault_rate));
}

void load_all_settings() {
	// key_type
	s_key_type = get_settings("s_key_type").toInt();
	// bee_freq
	s_bee_freq = get_settings("s_bee_freq").toInt();
	// auto_send_time
	s_auto_send_time = get_settings("s_auto_send_time").toInt();
	// shake_time
	s_shake_time = get_settings("s_shake_time").toInt();
	// play_u_time
	s_play_u_time = get_settings("s_play_u_time").toInt();
	// u_time
	s_u_time = get_settings("s_u_time").toInt();
	// auto_key_type
	s_auto_key_type = get_settings("s_auto_key_type").toInt();
	// auto_send
	s_auto_send = get_settings("s_auto_send").toInt();
	// touch_key
	s_touch_key = get_settings("s_touch_key").toInt();
	// touch_val
	s_touch_val = get_settings("s_touch_val").toInt();
	// s_exa_mode
	s_exa_mode = get_settings("s_exa_mode").toInt();
	// s_di_da_scale
	s_di_da_scale = get_settings("s_di_da_scale").toFloat();
	// s_fault_rate
	s_fault_rate = get_settings("s_fault_rate").toFloat();
}

void show_all_settings() {
	// key_type
	Serial.print("s_key_type = ");
	Serial.println(get_settings("s_key_type").toInt());
	// bee_freq
	Serial.print("s_bee_freq = ");
	Serial.println(get_settings("s_bee_freq").toInt());
	// s_split_time
	Serial.print("s_split_time = ");
	Serial.println(get_settings("s_split_time").toInt());
	// auto_send_time
	Serial.print("s_auto_send_time = ");
	Serial.println(get_settings("s_auto_send_time").toInt());
	// shake_time
	Serial.print("s_shake_time = ");
	Serial.println(get_settings("s_shake_time").toInt());
	// play_u_time
	Serial.print("s_play_u_time = ");
	Serial.println(get_settings("s_play_u_time").toInt());
	// u_time
	Serial.print("s_u_time = ");
	Serial.println(get_settings("s_u_time").toInt());
	// auto_key_type
	Serial.print("s_auto_key_type = ");
	Serial.println(get_settings("s_auto_key_type").toInt());
	// auto_send
	Serial.print("s_auto_send = ");
	Serial.println(get_settings("s_auto_send").toInt());
	// touch_key
	Serial.print("s_touch_key = ");
	Serial.println(get_settings("s_touch_key").toInt());
	// touch_val
	Serial.print("s_touch_val = ");
	Serial.println(get_settings("s_touch_val").toInt());

	// s_exa_mode
	Serial.print("s_exa_mode = ");
	Serial.println(get_settings("s_exa_mode").toInt());

	// s_di_da_scale
	Serial.print("s_di_da_scale = ");
	Serial.println(get_settings("s_di_da_scale").toFloat());

	// s_fault_rate
	Serial.print("s_fault_rate = ");
	Serial.println(get_settings("s_fault_rate").toFloat());
}

#endif