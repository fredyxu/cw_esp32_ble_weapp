#ifndef _OP_CODE_H
#define _OP_CODE_H

// 函数声明

// 识别空格
void check_space();
// 检查发送
void check_send();
// 播放电码
void play_code(String p_code);

#include "ble.h"

// 识别空格
void check_space() {
	if(!flag_space) {
		return ;
	}

	int diff_time = millis() - cs_time;
	if(flag_space && diff_time > (s_u_time * 2)) {
		cs_time = millis();

		ble_send("code", " ");

		// 如果是第一次的空格，则将空格times置否
		if(flag_space_times) {
			flag_space_times = false;
		}
		// 如果是第二次空格，则重置检查项目，并将检查发送打开
		else if(!flag_space_times) {
			flag_space_times = true;
			flag_space = false;
			flag_send = true;
			cs_time = millis();
		}
	}
}

void check_send() {
	if(!flag_send) {
		return ;
	}
	int diff_time = millis() - cs_time;
	if(diff_time > s_auto_send_time) {
		ble_send("cmd", "send");
		flag_send = false;
		cs_time = millis();
	}

}

// 播放电码
void play_code(String p_code)
{
	for (int i = 0; i < p_code.length(); i++)
	{
		if (p_code[i] == '.')
		{
			bee(true);
			int s = millis();
			delay(s_play_u_time - (millis() - s));
			bee(false);
			delay(s_play_u_time * 0.2);
		}
		else if (p_code[i] == '-')
		{
			bee(true);
			int s = millis();
			delay(s_play_u_time * 2 - (millis() - s));
			bee(false);
			delay(s_play_u_time * 0.2);
		}
		else if (p_code[i] == ' ')
		{
			// delay(s_split_time * 1.5);
			if(s_split_time < 80) {
				delay(80);
			}
			else {
				delay(s_split_time);
			}
			
		}
	}
}



#endif