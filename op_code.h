#ifndef _OP_CODE_H
#define _OP_CODE_H

// 函数声明

// 识别空格
void check_space();
// 检查发送
void check_send();
// 播放电码
void play_code(String p_code);
// 在多核播放电码
void play_code_core(String code_list, int core);
void play_code_core_do(void * pvParameters);

#include "ble.h"

void play_code_core(String code_list, int core) {
	var_code_list = code_list;
	xTaskCreatePinnedToCore(play_code_core_do, "play_code_core", 10000, NULL, 1, NULL,  core);
}

void play_code_core_do(void *v) {
	if(var_code_list != "") {
		for(int i = 0; i < var_code_list.length(); i ++) {
			String c = String(var_code_list[i]);
			if(flag_play_code) {
				play_code(c);

				if(c == " ") {
					ble_send_core("cmd:play_done", 0);
				}
			}
			else {
				var_code_list = "";
				vTaskDelete(NULL);
				return;
			}
		}
		// ble_send_core("cmd:play_done", 0);
		ble_send("cmd", "play_done");
	}
	var_code_list = "";
	vTaskDelete(NULL);
}

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
	// 间隔时长
	int sp_time = s_play_u_time;
	for (int i = 0; i < p_code.length(); i++)
	{
		if (p_code[i] == '.')
		{
			bee(true);
			delay(s_play_u_time);
			bee(false);
			delay(sp_time);
		}
		else if (p_code[i] == '-')
		{
			bee(true);
			delay(s_play_u_time * s_di_da_scale);
			bee(false);
			delay(sp_time);
		}
		else if (p_code[i] == ' ')
		{
			
			if(s_split_time * 3 < 80) {
				delay(80);
			}
			else {
				delay(sp_time * 3);
			}
			
		}
	}
	
}






#endif